package com.bjfu.demo.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor

//"ID", "姓名", "性别","年龄","电话","职位","入职时间","薪水","部门"
public class Employee {
    private String id;
    private String name;
    private String gender;
    private int age;
    private String phone;
    private String position;
    private String hireDate;
    private double salary;
    private String department;

}
