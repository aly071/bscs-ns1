#SALANATIN, NATHALY PEARL | BSCS NS 2AB
import os
print("LOCAL VARIABLE\n")
def record_input():
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

        os.system('cls')
    display_records(name, q_one, q_two, q_three)

def display_records(names, q11, q22, q33):
    print("\n\tName\tQ1\t\tQ2\t\tQ3\t\tAve\t\t\tRemarks") #header

    for i in range(0,2):

        average = (q11[i] + q22[i] + q33[i]) / 3

        if average >= 75:
            remarks = "PASSED"
        else:
            remarks = "FAILED"
        
        print(str(i+1) + ".)\t" + names[i] + "\t\t" + str(q11[i]) + "\t\t" + str(q22[i]) + "\t\t" + str(q33[i]) + "\t\t" + str('%.2f' % average) + "\t\t" + remarks)

record_input()
