from os import sep,write

class Mnemonics:
    def __init__(self):
        self.AD={
            "START":1,
            "END" :2,
            "ORIGIN":3,
            "EQU":4,
            "LTORG":5,
        }

        self.IS={
            "STOP":0,
            "ADD":1,
            "SUB":2,
            "MULT":3,
            "MOVER":4,
            "MOVEM":5,
            "COMP":6,
            "BC":7,
            "DIV":8,
            "READ":9,
            "PRINT":10
        }

        self.DL={
            "DC":1,
            "DS":2
        }

        self.REG={
            "AREG":1,
            "BREG":2,
            "CREG":3,
            "DREG":4
        }

        self.CC={
            "LT":1,
            "LE":2,
            "EQ":3,
            "GT":4,
            "GE":5,
            "ANY":6
        }

    def getClass(self,string):
            if string in self.AD:
                return "AD"
            elif string in self.IS:
                return "IS"
            elif string in self.DL:
                return "DL"
            elif string in self.CC:
                return "CC"
            elif string in self.REG:
                return "REG"
            else:
                return ""

    def getMachinecode(self,string):
            if string in self.AD:
                return self.AD[string]
            elif string in self.IS:
                return self.IS[string]
            elif string in self.DL:
                return self.DL[string]
            elif string in self.CC:
                return self.CC[string]
            elif string in self.REG:
                return  self.REG[string]
            else:
                return -1


class pass1:
    def __init__ (self):
        self.lookup=Mnemonics()
        self.location=0
        self.ic=[]
        self.poolTab=[0]
        self.symTab={}
        self.literalTab={}
        self.litptr=0
        self.littabIndex=0
        self.code=open("input.txt","r")
        self.ltabFile=open("Littab.txt","w")
        self.SymtabFile=open("SybTab.txt","w")
        self.poolfile=open("PoolTab.txt","w")
        self.ICfile=open("IntermediateCode.txt","w")

    def calculate(self,string):

        if "+" in string:
            string=string.split("+")
            print(self.symTab)
            return int(self.symTab[string[0]]) + int(string[1])

        if "-" in string:
            string=string.split("-")
            return int(self.symTab[string[0]]) + int(string[1])

        else:
            addr=int(self.symTab[string])
            return addr

    def process(self):
        for line in self.code.readlines():
            self.ic.append([])
            line=line.strip("\n")
            line=line.split("\t")

            if line[0]!="" :
                if line[0] in self.symTab:
                    self.symTab[line[0]]=self.location
                else:
                    self.symTab[line[0]]=self.location
            
            if line[1]=="START":
                self.location=int(line[2])
                self.ic[-1].append(("AD",1))
                self.ic[-1].append(("C",self.location))

            elif line[1]=="ORIGIN":
                self.location=self.calculate(line[2])
                self.ic[-1].append(("AD",3))
                self.ic[-1].append(self.location)
                # equation
                # sign=""
                # if '+' in string:
                #     sign="+"
                #     equation=string.split("+")
                # if '-' in string:
                #     sign="+"
                #     equation=string.split("-")
                # self.ic[-1].append(("S",self.symTab[equation[0]],sign,equation[1]))
                
            elif line[1]=="EQU":
                self.ic[-1].append(("AD",4))
                newlocation =  self.calculate(line[2])
                self.symTab[line[0]] = newlocation
                self.ic[-1].append(("C",newlocation))

            elif line[1]=="LTORG":
                
                for i in range(self.poolTab[-1],len(self.literalTab)):
                    self.ic[-1].append(("DL",1))
                    self.literalTab[i][1]=self.location
                    constant=self.literalTab[i][0]
                    self.ic[-1].append(("C",constant))
                    self.location+=1
                    self.litptr+=1

                    if i<len(self.literalTab):
                        self.ic.append([])
                self.poolTab.append(self.litptr)

            elif line[1]=="END":
                self.ic[-1].append(("AD",2))
                if self.litptr != len(self.literalTab):
                    for i in range(self.poolTab[-1],len(self.literalTab)):
                        self.ic[-1].append(("DL",1))
                        self.literalTab[i][1]=self.location
                        constant=self.literalTab[i][0]
                        self.ic[-1].append(("C",constant))
                        self.ic[-1].append(self.location)
                        self.location+=1
                        self.litptr+=1

                        if i<len(self.literalTab):
                            self.ic.append([])
                    self.poolTab.append(self.litptr)

            elif line[1]=="DC":
                self.ic[-1].append(("DL",1))
                constant=int(line[2])
                self.ic[-1].append(("C",constant))
                self.ic[-1].append(self.location)
                self.location+=1

            elif line[1]=="DS":
                self.ic[-1].append(("DL",2))
                constant=int(line[2])
                self.ic[-1].append(("C",constant))
                self.ic[-1].append(self.location)
                self.location+=constant

            elif line[1]=="BC":
                self.ic[-1].append(("IS",7))
                Class=self.lookup.getClass(line[2])
                mc=self.lookup.getMachinecode(line[2])
                self.ic[-1].append((Class,mc))
                if line[3] not in self.symTab:
                    self.symTab[line[3]]=None
                symindex=list(self.symTab.keys())
                self.ic[-1].append(("S",symindex.index(line[3])))
                self.ic[-1].append(self.location)
                self.location+=1
            elif line[1] == "STOP":
                self.ic[-1].append(("IS",0))
                self.ic[-1].append(self.location)
                self.location += 1

            else:
                iccode=self.lookup.getClass(line[1])
                icnum=self.lookup.getMachinecode(line[1])
                self.ic[-1].append((iccode,icnum))

                iccode=self.lookup.getClass(line[2])
                icnum=self.lookup.getMachinecode(line[2])
                self.ic[-1].append((iccode,icnum))

                if "=" in line[3]:
                    lit=line[3].strip("=")
                    lit=int(lit.strip("'"))
                    self.literalTab[self.littabIndex]=[lit,None]
                    self.ic[-1].append(("L",self.littabIndex))
                    self.ic[-1].append(self.location)
                    self.littabIndex+=1

                else:
                    if line[3] in self.symTab:
                        symbolTableKeys = list(self.symTab.keys())
                        self.ic[-1].append(("S",symbolTableKeys.index(line[3])))
                        self.ic[-1].append(self.location)
                    else:
                        self.symTab[line[3]] = None
                        symbolTableKeys = list(self.symTab.keys())
                        self.ic[-1].append(("S",symbolTableKeys.index(line[3])))
                        self.ic[-1].append(self.location)

                self.location+=1

        self.printIC()
        self.printSymTab()
        self.printLittab()
        self.printPooltab()

    def printIC(self):
        tab = "\t"
        endline = "\n"
        print("INTERMEDIATE CODE: \n")
        for code in self.ic:
            line=""
            for i in range(len(code)):
               line+=str(code[i])
               if i!=len(code):
                 line+=tab
            line+=endline
            print(line,end="")
            self.ICfile.write(line)
        self.ICfile.close()

    def printSymTab(self):
        tab = "\t"
        endline = "\n"
        print("SYMBOL TABLE: \n")
        for index,sym in enumerate(self.symTab):
            line=str(index)+tab+str(sym)+tab+str(self.symTab[sym])+endline
            print(line,end="")
            self.SymtabFile.write(line)
        self.SymtabFile.close()

    def printLittab(self):
        tab = "\t"
        endline = "\n"
        print("LITTAB: \n")
        for i in range(len(self.literalTab)):
            line=str(i)+tab+str(self.literalTab[i][0])+tab+str(self.literalTab[i][1])+endline
            print(line,end="")
            self.ltabFile.write(line)
        self.ltabFile.close()

    def printPooltab(self):
        tab = "\t"
        endline = "\n"
        print("POOLTAB: \n")
        for i in self.poolTab:
            line=str(i)+endline
            self.poolfile.write(line)
        self.poolfile.close()
            
obj=pass1()
obj.process()
            

            