package lista7;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

// import lista7.Broomstick;

public class BroomstickEdit extends JComponent implements ActionListener {
    Broomstick obj;

    String file;

    JTextField wheels;
    JTextField production_year;
    JTextField brand;
    JTextField max_speed;

    public BroomstickEdit(Broomstick obj, String file) {
        this.obj = obj;
        this.file = file;
        wheels = new JTextField(String.valueOf(obj.wheels));
        production_year = new JTextField(String.valueOf(obj.production_year));
        brand = new JTextField(obj.brand);
        max_speed = new JTextField(String.valueOf(obj.max_speed));
    }

    public void run() {
        JFrame frame = new JFrame("Broomstick Edit");
        frame.setSize(350, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        Container c = frame.getContentPane();
        c.setLayout(new GridLayout(5, 2));
        create(c);
        frame.setVisible(true);
    }

    void create(Container c) {
        c.add(new JLabel("Wheels"));
        c.add(wheels);
        c.add(new JLabel("Production year"));
        c.add(production_year);
        c.add(new JLabel("Brand"));
        c.add(brand);
        c.add(new JLabel("Max Speed"));
        c.add(max_speed);

        JButton button = new JButton("Save");
        button.addActionListener(this);
        c.add(button);
    }

    public void actionPerformed(ActionEvent e) {
        obj.wheels = Integer.valueOf(wheels.getText());
        obj.production_year = Integer.valueOf(production_year.getText());
        obj.brand = brand.getText();
        obj.max_speed = Integer.valueOf(max_speed.getText());

        Broomstick.saveObject(obj, file);
    }
}
