package com.bjfu.demo.ui;

import com.bjfu.demo.bean.Employee;

import javax.swing.*;
import javax.swing.plaf.FontUIResource;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;

public class EmployeeManagementUI extends JFrame {
    private ArrayList<Employee> employeeList = new ArrayList<>();
    private JTextField searchField;
    private JTable table;
    private DefaultTableModel tableModel;
    private String[] columns = {"ID", "姓名", "性别","年龄","电话","职位","入职时间","薪水","部门"};
    private int currentPage = 1;
    private final int ROWS_PER_PAGE = 20;

    public EmployeeManagementUI(String username) {
        setTitle("员工信息管理系统-" + username);
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // 设置全局字体以避免中文乱码
        setUIFont(new FontUIResource(new Font("微软雅黑", Font.PLAIN, 14)));

        initUI();
        setVisible(true);
    }


    private void initUI() {
        // 第一行面板：输入框 + 搜索按钮 + 添加按钮
        JPanel topPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
        searchField = new JTextField(20);
        JButton searchButton = new JButton("搜索");
        JButton addButton = new JButton("添加");

        topPanel.add(searchField);
        topPanel.add(searchButton);
        topPanel.add(addButton);

        // 表格模型与表格初始化
        tableModel = new DefaultTableModel(columns, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return false; // 不允许直接编辑
            }
        };
        table = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(table);

        // 添加右键菜单
        JPopupMenu popupMenu = new JPopupMenu();
        JMenuItem editItem = new JMenuItem("修改");
        JMenuItem deleteItem = new JMenuItem("删除");

        popupMenu.add(editItem);
        popupMenu.add(deleteItem);

        table.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                if (SwingUtilities.isRightMouseButton(e)) {
                    int row = table.rowAtPoint(e.getPoint());
                    if (row >= 0 && row < table.getRowCount()) {
                        table.setRowSelectionInterval(row, row);
                    }
                    popupMenu.show(e.getComponent(), e.getX(), e.getY());
                }
            }
        });

        // 修改功能
        editItem.addActionListener(e -> {
            int selectedRow = table.getSelectedRow();
            if (selectedRow != -1) {
                showEditDialog(selectedRow);
            } else {
                JOptionPane.showMessageDialog(this, "请先选择一行数据进行修改。");
            }
        });

        // 删除功能
        deleteItem.addActionListener(e -> {
            int selectedRow = table.getSelectedRow();
            if (selectedRow != -1) {
                tableModel.removeRow(selectedRow);
                employeeList.remove(selectedRow);
            } else {
                JOptionPane.showMessageDialog(this, "请先选择一行数据进行删除。");
            }
        });

        // 添加按钮事件
        addButton.addActionListener(e -> showAddDialog());

        // 添加组件到主窗口
        add(topPanel, BorderLayout.NORTH);
        add(scrollPane, BorderLayout.CENTER);

        searchButton.addActionListener(e -> searchEmployee());
    }

    // 显示添加员工对话框
    private void showAddDialog() {
        JPanel panel = new JPanel(new GridLayout(9, 2));
        JTextField idField = new JTextField();
        JTextField nameField = new JTextField();
        JTextField sexField = new JTextField();
        JTextField ageField = new JTextField();
        JTextField phoneField = new JTextField();
        JTextField positionField = new JTextField();
        JTextField hiredateField = new JTextField();
        JTextField salaryField = new JTextField();
        JTextField departmentField = new JTextField();

        panel.add(new JLabel("ID:"));
        panel.add(idField);
        panel.add(new JLabel("姓名:"));
        panel.add(nameField);
        panel.add(new JLabel("性别:"));
        panel.add(sexField);
        panel.add(new JLabel("年龄:"));
        panel.add(ageField);
        panel.add(new JLabel("电话:"));
        panel.add(phoneField);
        panel.add(new JLabel("职位:"));
        panel.add(positionField);
        panel.add(new JLabel("入职时间:"));
        panel.add(hiredateField);
        panel.add(new JLabel("薪水:"));
        panel.add(salaryField);
        panel.add(new JLabel("部门:"));
        panel.add(departmentField);


        int result = JOptionPane.showConfirmDialog(null, panel,
                "添加员工信息", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            Employee employee = new Employee (idField.getText(), nameField.getText(), sexField.getText(),
                    Integer.parseInt(ageField.getText()), phoneField.getText(),
                    positionField.getText(), hiredateField.getText(),
                    Double.parseDouble(salaryField.getText()), departmentField.getText());
            employeeList.add(employee);

            tableModel.addRow(new Object[]{

                    idField.getText(),
                    nameField.getText(),
                    sexField.getText(),
                    ageField.getText(),
                    phoneField.getText(),
                    positionField.getText(),
                    hiredateField.getText(),
                    salaryField.getText(),
                    departmentField.getText(),
            });
            JOptionPane.showMessageDialog(this, "员工信息添加成功！");
        }
    }

    // 显示修改对话框
    private void showEditDialog(int row) {
        JPanel panel = new JPanel(new GridLayout(9, 2));
        JTextField idField = new JTextField((String) tableModel.getValueAt(row, 0));
        JTextField nameField = new JTextField((String) tableModel.getValueAt(row, 1));
        JTextField positionField = new JTextField((String) tableModel.getValueAt(row, 2));
        JTextField departmentField = new JTextField((String) tableModel.getValueAt(row, 3));
        JTextField phoneField = new JTextField((String) tableModel.getValueAt(row, 4));
        JTextField sexField = new JTextField((String) tableModel.getValueAt(row, 5));
        JTextField ageField = new JTextField((String) tableModel.getValueAt(row, 6));
        JTextField hiredateField = new JTextField((String) tableModel.getValueAt(row, 7));
        JTextField salaryField = new JTextField((String) tableModel.getValueAt(row, 8));

        panel.add(new JLabel("ID:"));
        panel.add(idField);
        panel.add(new JLabel("姓名:"));
        panel.add(nameField);
        panel.add(new JLabel("性别:"));
        panel.add(sexField);
        panel.add(new JLabel("年龄:"));
        panel.add(ageField);
        panel.add(new JLabel("电话:"));
        panel.add(phoneField);
        panel.add(new JLabel("职位:"));
        panel.add(positionField);
        panel.add(new JLabel("入职时间:"));
        panel.add(hiredateField);
        panel.add(new JLabel("薪水:"));
        panel.add(salaryField);
        panel.add(new JLabel("部门:"));
        panel.add(departmentField);

        int result = JOptionPane.showConfirmDialog(null, panel,
                "修改员工信息", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            tableModel.setValueAt(idField.getText(), row, 0);
            tableModel.setValueAt(nameField.getText(), row, 1);
            tableModel.setValueAt(positionField.getText(), row, 2);
            tableModel.setValueAt(departmentField.getText(), row, 3);
            tableModel.setValueAt(phoneField.getText(), row, 4);
            tableModel.setValueAt(sexField.getText(), row, 5);
            tableModel.setValueAt(ageField.getText(), row, 6);
            tableModel.setValueAt(hiredateField.getText(), row, 7);
            tableModel.setValueAt(salaryField.getText(), row, 8);

            Employee employee = employeeList.get(row);
            employee.setId(idField.getText());
            employee.setName(nameField.getText());
            employee.setPosition(positionField.getText());
            employee.setDepartment(departmentField.getText());
            employee.setPhone(phoneField.getText());
            employee.setGender(sexField.getText());
            employee.setAge(Integer.parseInt(ageField.getText()));
            employee.setHireDate(hiredateField.getText());
            employee.setSalary(Double.parseDouble(salaryField.getText()));
        }
    }


    // 搜索功能
    private void searchEmployee() {
        String searchText = searchField.getText();
        tableModel.setRowCount(0);
        for (Employee employee : employeeList) {
            if (employee.getName().contains(searchText) || employee.getId().contains(searchText)) {
                tableModel.addRow(new Object[]{
                        employee.getId(),
                        employee.getName(),
                        employee.getGender(),
                        employee.getAge(),
                        employee.getPhone(),
                        employee.getPosition(),
                        employee.getHireDate(),
                        employee.getSalary(),
                        employee.getDepartment(),
                });
            }
        }
    }



    // 设置Swing全局字体以支持中文
    public static void setUIFont(FontUIResource f) {
        UIManager.put("Button.font", f);
        UIManager.put("Label.font", f);
        UIManager.put("TextField.font", f);
        UIManager.put("Table.font", f);
        UIManager.put("OptionPane.messageFont", f);
    }

}

