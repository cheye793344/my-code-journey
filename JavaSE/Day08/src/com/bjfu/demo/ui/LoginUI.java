package com.bjfu.demo.ui;

import javax.swing.*;
import javax.swing.plaf.FontUIResource;
import java.awt.*;

public class LoginUI extends JFrame {
    private JTextField usernameField;
    private JPasswordField passwordField;
    private JButton loginButton;
    private JButton registerButton;

    // 自定义字体
    private Font customFont = new Font("微软雅黑", Font.PLAIN, 18);
    private Color primaryColor = new Color(66, 135, 245);

    public LoginUI() {
        super("登录-人事管理系统");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 400);
        setLocationRelativeTo(null); // 居中显示

        // 设置全局字体以支持中文
        setUIFont(new FontUIResource(customFont));

        CreateAndShowGUI();
    }

    public void CreateAndShowGUI() {
        JPanel panel = new JPanel();
        panel.setLayout(null);
        panel.setBackground(new Color(240, 240, 240));

        // 标题
        JLabel titleLabel = new JLabel("登录");
        titleLabel.setBounds(50, 30, 300, 30);
        titleLabel.setFont(new Font("微软雅黑", Font.BOLD, 24));
        panel.add(titleLabel);

        // 用户名标签
        JLabel usernameLabel = new JLabel("用户名:");
        usernameLabel.setBounds(50, 100, 150, 30);
        usernameLabel.setFont(customFont);
        panel.add(usernameLabel);

        // 用户名输入框
        usernameField = new JTextField();
        usernameField.setBounds(160, 100, 190, 30);
        usernameField.setFont(customFont);
        panel.add(usernameField);

        // 密码标签
        JLabel passwordLabel = new JLabel("密   码: ");
        passwordLabel.setBounds(50, 150, 150, 30);
        passwordLabel.setFont(customFont);
        panel.add(passwordLabel);

        // 密码输入框
        passwordField = new JPasswordField();
        passwordField.setBounds(160, 150, 190, 30);
        passwordField.setFont(customFont);
        panel.add(passwordField);

        // 登录按钮
        loginButton = new JButton("登   录");
        loginButton.setBounds(200, 200, 150, 30);
        loginButton.setFont(customFont);
        loginButton.setBackground(primaryColor);
        loginButton.setForeground(Color.WHITE);
        panel.add(loginButton);

        // 注册按钮
        registerButton = new JButton("注   册");
        registerButton.setBounds(50, 200, 150, 30);
        registerButton.setFont(customFont);
        registerButton.setBackground(Color.WHITE);
        registerButton.setForeground(Color.BLACK);
        panel.add(registerButton);
        registerButton.addActionListener(e -> new RegisterAdminUI());

        add(panel);
        setVisible(true);
    }

    /**
     * 设置Swing全局字体以支持中文显示
     */
    public static void setUIFont(FontUIResource f) {
        UIManager.put("Button.font", f);
        UIManager.put("Label.font", f);
        UIManager.put("TextField.font", f);
        UIManager.put("PasswordField.font", f);
        UIManager.put("OptionPane.messageFont", f);
    }
}
