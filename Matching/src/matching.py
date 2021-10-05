# matching.py
#   Created on: 2021/10/05
#       Author: a_takeuchi
#
#   病院の就活のマッチング

import random

class Hospital:
    def __init__(self, name, p_num):
        self.name = name
        self.p_num = p_num
        self.p_match = []
        self.result_id = []

class Student:
    def __init__(self, name):
        self.name = name
        self.p_match = []
        self.result_id = []


def main():
    print(__name__)

    hospital_num = 10
    student_num = 25

    students = initialize_student(student_num, hospital_num)
    hospitals = initialize_hospital(hospital_num, students)
    matching(hospitals, students)

    for i in range(student_num):
        print(i, end="\t")
        # print(i, "\tStudent: ", students[i].name, end="\t")
        print("Place: ", students[i].result_id, end="\t")
        print("Aspire: ", students[i].p_match)
        
    for i in range(hospital_num):
        print(i, end="\t")
        # print(i, "\tHospital: ", hospitals[i].name, end="\t")
        print("students: ", hospitals[i].result_id, end="\t")
        print("num: ", hospitals[i].p_num, end="\t")
        print("Aspire: ", hospitals[i].p_match)

def pro_match(i, students, hospitals):
    student = students[i]
    for hospital_id in student.p_match:
        hospital = hospitals[hospital_id]
        if i in hospital.p_match:
            if len(hospital.result_id) < hospital.p_num:
                hospital.result_id.append(i)
                student.result_id.append(hospital_id)
                break
            else:
                worst = -1
                worst_id = 0
                for id in hospital.result_id:
                    if hospital.p_match.index(id) > worst:
                        worst = hospital.p_match.index(id)
                        worst_id = id
                if hospital.p_match.index(i) < worst:
                    hospital.result_id.remove(worst_id)
                    students[worst_id].result_id.remove(hospital_id)
                    hospital.result_id.append(i)
                    student.result_id.append(hospital_id)
                    break
            



def matching(hospitals, students):
    not_match_before = []
    while True:
        not_match = []
        for i, student in enumerate(students):
            if not student.result_id:
                not_match.append(i)
                pro_match(i, students, hospitals)
        if not_match == not_match_before:
            break
        not_match_before = not_match


# 学生それぞれについて、志望する病院とその志望順を設定する
def initialize_student(student_num, hospital_num):
    students = []
    for student in range(student_num):
        # 志望する病院の数をランダムに設定
        p_num = random.randrange(2, hospital_num)
        name = chr(ord('A') + student)
        students.append(Student(name))

        # 志望順をランダムに設定
        for i in range(p_num):
            while True:
                add = random.randrange(hospital_num)
                if add not in students[student].p_match:
                    students[student].p_match.append(add)
                    break
            i += 1
        student += 1
    return students


def initialize_hospital(hospital_num, students):
    hospitals = []
    for hospital in range(hospital_num):
        # 名前と募集人数を設定
        p_num = random.randrange(1, 6)
        name = chr(ord('a') + hospital)
        hospitals.append(Hospital(name, p_num))

        # 応募している学生を探す
        students_id = []
        for i, student in enumerate(students):
            if hospital in student.p_match:
                students_id.append(i)
        
        # 募集人数に達するか志望者がいなくなるまで、学生の順位を設定
        q_num = random.randrange(p_num, len(students))
        n = min(q_num, len(students_id))
        hospitals[hospital].p_match = random.sample(students_id, n)
        hospital += 1
    return hospitals



if __name__ == '__main__':
    main()
