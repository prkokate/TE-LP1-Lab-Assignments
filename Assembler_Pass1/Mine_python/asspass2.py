import re
pattern=re.compile(r'\(\'([A-Z]{,2})\',\s(\d+)\)')  


tab="\t"
class pass2:
    def __init__(self):
        self.ICfile=open("IntermediateCode.txt","r")
        self.literalTableFile=open("Littab.txt","r")
        self.symbolTableFile=open("SybTab.txt")
        self.outputFile=open("Output.txt", "w")
        self.symTab={}
        self.litTab={}
    
    def Tostring(self,num):
        num=str(num)
        if len(num)==1:
            return '00'+num
        if len(num)==2:
            return '0'+num
        else:
            return num
    
    def readSymtab(self):
        print("\nSymbol table:\n")
        for line in self.symbolTableFile.readlines():
            line=line.strip("\n")
            line=line.split("\t")
            key=int(line[0])
            # sym=line[1]
            value=int(line[2])
            self.symTab[key]=value
            print(key,value,sep="\t")
        print("\n")

    def readLittab(self):
        print("\nLiteral table:\n")
        for line in self.literalTableFile.readlines():
            line=line.strip("\n")
            line=line.split("\t")
            key=int(line[0])
            # sym=line[1]
            value=int(line[2])
            self.litTab[key]=value
            print(key,value,sep="\t")
        print("\n")

    def process(self):
        self.readSymtab()
        self.readLittab()
        for line in self.ICfile.readlines():
            line=line.strip("\n")
            line=line.split("\t")
            parseLine=""
            find=pattern.search(line[0])

            if find.group(1)=="IS" or find.group(1)=="DL":
                location=line[-2]
                parseLine+=location+tab

                if find.group(1)=="IS":
                    parseLine+=self.Tostring(find.group(2))+tab

                    if find.group(2)=="10" or find.group(2)=="9":
                        find=pattern.search(line[1])
                        parseLine+="000"+tab+self.Tostring(self.symTab[int(find.group(2))])+"\n"
                    elif find.group(2)=="0":
                        parseLine+="000"+tab+"000"+"\n"
                    else:
                        find=pattern.search(line[1])
                        parseLine+=self.Tostring(find.group(2))+tab

                        find=pattern.search(line[2])
                        if find.group(1)=="S":
                            key=int(find.group(2))
                            parseLine+=self.Tostring(self.symTab[key])+"\n"
                        elif find.group(1)=="L":
                            key=int(find.group(2))
                            parseLine+=self.Tostring(self.litTab[key])+"\n"

                else:
                    if(find.group(2)=="2"):
                        parseLine+="000"+tab+"000"+tab+"000"+"\n"
                    else:
                        find=pattern.search(line[1])
                        parseLine+="000"+tab+"000"+tab+self.Tostring(find.group(2))+"\n"
            
            else:
                continue
            print(parseLine,end="")
            self.outputFile.write(parseLine)
        self.outputFile.close()
        self.symbolTableFile.close()
        self.literalTableFile.close()

obj=pass2()
obj.process()


            
        
