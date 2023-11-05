package lista7;

import java.io.*;

public class Car extends Vehicle {
    public String model;

    public Car() {
        this(4, 2000, "Ford", "Focus");
    }

    public Car(int wheels, int production_year, String brand, String model) {
        super(wheels, production_year, brand);
        this.model = model;
    }

    @Override
    public String toString() {
        String s = super.toString();
        s.replace("]", (", model=" + model + "]"));
        return s;
    }

    public static void saveObject(Car obj, String file) {
        try {
            FileOutputStream fos = new FileOutputStream(file);
            ObjectOutputStream oos = new ObjectOutputStream(fos);

            oos.writeObject(obj);
            fos.close();
            oos.close();
        } catch (IOException e) {
            System.out.println("cant save object");
        }
    }

    public static Car readObject(String file) {
        try {
            FileInputStream fis = new FileInputStream(file);
            ObjectInputStream ois = new ObjectInputStream(fis);

            Car obj = (Car) ois.readObject();
            fis.close();
            ois.close();
            return obj;
        } catch (FileNotFoundException e) {
            return new Car();
        } catch (IOException e) {
            System.out.println("cant read object");
        } catch (ClassNotFoundException e) {
            System.out.println("Car not found");
        }
        return null;
    }

    public void editor(String file) {
        CarEdit editor = new CarEdit(this, file);
        editor.run();
    }
}