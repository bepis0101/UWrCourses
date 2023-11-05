package lista7;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

// import lista7.Vehicle;

public class VehicleEdit extends JComponent implements ActionListener {

    Vehicle obj;

    String file;

    JTextField wheels;
    JTextField production_year;
    JTextField brand;

    public VehicleEdit(Vehicle obj, String file) {
        this.obj = obj;
        this.file = file;
        wheels = new JTextField(String.valueOf(obj.wheels));
        production_year = new JTextField(String.valueOf(obj.production_year));
        brand = new JTextField(obj.brand);
    }

    public void run() {
        JFrame frame = new JFrame("Vehicle Edit");
        frame.setSize(350, 200);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        Container c = frame.getContentPane();
        c.setLayout(new GridLayout(4, 2));
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

        JButton button = new JButton("Save");
        button.addActionListener(this);
        c.add(button);
    }

    public void actionPerformed(ActionEvent e) {
        obj.wheels = Integer.valueOf(wheels.getText());
        obj.production_year = Integer.valueOf(production_year.getText());
        obj.brand = brand.getText();

        Vehicle.saveObject(obj, file);
    }
}
