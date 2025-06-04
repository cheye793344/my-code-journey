package com.bjfu.demo.ui;

import javax.swing.*;
import javax.swing.plaf.FontUIResource;
import java.awt.*;
import java.awt.event.*;

public class RegisterAdminUI extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JPasswordField confirmPasswordField;
    private JButton registerButton;

    // 自定义字体和颜色
    private Font customFont = new Font("微软雅黑", Font.PLAIN, 18);
    private Color primaryColor = new Color(66, 135, 245);

    public RegisterAdminUI() {
        super("注册管理员");
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE); // 关闭窗口不退出程序
        setSize(400, 400);
        setLocationRelativeTo(null); // 居中显示

        // 设置全局字体以支持中文

        createAndShowGUI();
    }

    private void createAndShowGUI() {
        JPanel panel = new JPanel();
        panel.setLayout(null);
        panel.setBackground(new Color(240, 240, 240));

        // 标题
        JLabel titleLabel = new JLabel("注册管理员");
        titleLabel.setBounds(100, 30, 300, 30);
        titleLabel.setFont(new Font("微软雅黑", Font.BOLD, 24));
        panel.add(titleLabel);

        // 用户名标签 + 输入框
        JLabel usernameLabel = new JLabel("用户名:");
        usernameLabel.setBounds(50, 100, 100, 30);
        usernameLabel.setFont(customFont);
        panel.add(usernameLabel);

        usernameField = new JTextField();
        usernameField.setBounds(160, 100, 190, 30);
        usernameField.setFont(customFont);
        panel.add(usernameField);

        // 密码标签 + 输入框
        JLabel passwordLabel = new JLabel("密   码: ");
        passwordLabel.setBounds(50, 150, 100, 30);
        passwordLabel.setFont(customFont);
        panel.add(passwordLabel);

        passwordField = new JPasswordField();
        passwordField.setBounds(160, 150, 190, 30);
        passwordField.setFont(customFont);
        panel.add(passwordField);

        // 确认密码标签 + 输入框
        JLabel confirmPasswordLabel = new JLabel("确认密码:");
        confirmPasswordLabel.setBounds(50, 200, 100, 30);
        confirmPasswordLabel.setFont(customFont);
        panel.add(confirmPasswordLabel);

        confirmPasswordField = new JPasswordField();
        confirmPasswordField.setBounds(160, 200, 190, 30);
        confirmPasswordField.setFont(customFont);
        panel.add(confirmPasswordField);

        // 注册按钮
        registerButton = new JButton("注   册");
        registerButton.setBounds(120, 260, 160, 35);
        registerButton.setFont(customFont);
        registerButton.setBackground(primaryColor);
        registerButton.setForeground(Color.WHITE);
        registerButton.addActionListener(this::handleRegister);
        panel.add(registerButton);

        add(panel);
        setVisible(true);
    }

    private void handleRegister(ActionEvent e) {
        String username = usernameField.getText().trim();
        char[] password = passwordField.getPassword();
        char[] confirmPassword = confirmPasswordField.getPassword();

        if (username.isEmpty()) {
            JOptionPane.showMessageDialog(this, "用户名不能为空！");
            return;
        }

        if (password.length == 0 || confirmPassword.length == 0) {
            JOptionPane.showMessageDialog(this, "密码不能为空！");
            return;
        }

        if (!new String(password).equals(new String(confirmPassword))) {
            JOptionPane.showMessageDialog(this, "两次输入的密码不一致！");
            return;
        }

        // TODO: 实际开发中应加密保存密码并写入数据库或文件
        JOptionPane.showMessageDialog(this, "注册成功！\n用户名：" + username);

        // 清空输入框
        usernameField.setText("");
        passwordField.setText("");
        confirmPasswordField.setText("");

        // 可选：关闭当前窗口
        dispose();
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new RegisterAdminUI());
    }
}

