package com.bjfu.demo.bean;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor

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

    public Employee(String id, String name, String gender, int age, String phone, String position, String hireDate,
			double salary, String department) {
		super();
		this.id = id;
		this.name = name;
		this.gender = gender;
		this.age = age;
		this.phone = phone;
		this.position = position;
		this.hireDate = hireDate;
		this.salary = salary;
		this.department = department;
	}

}
