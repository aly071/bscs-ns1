#SALANATIN, NATHALY PEARL | BSCS NS 2AB
print("GLOBAL VARIABLE\n")
import os
name = []
q_one = []
q_two = []
q_three = []

#input 
for i in range(0,2):

    name_in = str(input("Name: "))
    q1 = int(input("Quiz 1: "))
    q2 = int(input("Quiz 2: "))
    q3 = int(input("Quiz 3: "))

    name.append(name_in)   
    q_one.append(q1)
    q_two.append(q2)
    q_three.append(q3)

    os.system('cls') #clears screen after very loop

#display loop
print("\n\tName\tQ1\t\tQ2\t\tQ3\t\tAve\t\t\tRemarks") #header

for i in range(0,2):
    average = (q_one[i] + q_two[i] + q_three[i]) / 3
    if average >= 75:
        remarks = "PASSED"
    else:
        remarks = "FAILED"
    
    print(str(i+1) + ".)\t" + name[i] + "\t\t" + str(q_one[i]) + "\t\t" + str(q_two[i]) + "\t\t" + str(q_three[i]) + "\t\t" + str('%.2f' % average) + "\t\t" + remarks)
    

