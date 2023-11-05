package lista7;

import java.io.*;

public class Vehicle implements Serializable {
    private static final long serialVersionUID = 1L;

    public int wheels;
    public int production_year;
    public String brand;

    public Vehicle() {
        this(0, 0, " ");
    }

    public Vehicle(int wheels, int production_year, String brand) {
        this.wheels = wheels;
        this.production_year = production_year;
        this.brand = brand;
    }

    @Override
    public String toString() {
        return "Vehicle [wheels=" + wheels + ", production_year=" + production_year + ", brand=" + brand + "]";
    }

    public static void saveObject(Vehicle obj, String file) {
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

    public static Vehicle readObject(String file) {
        try {
            FileInputStream fis = new FileInputStream(file);
            ObjectInputStream ois = new ObjectInputStream(fis);

            Vehicle obj = (Vehicle) ois.readObject();
            fis.close();
            ois.close();
            return obj;
        } catch (FileNotFoundException e) {
            return new Vehicle();
        } catch (IOException e) {
            System.out.println("cant read object");
        } catch (ClassNotFoundException e) {
            System.out.println("vehicle not found");
        }
        return null;
    }

    public void editor(String file) {
        VehicleEdit editor = new VehicleEdit(this, file);
        editor.run();
    }
}