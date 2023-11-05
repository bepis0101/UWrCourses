package lista7;

import java.io.*;

public class Broomstick extends Vehicle {
    public int max_speed;

    public Broomstick() {
        this(0, 1980, "Nimbus 2000", 100);
    }

    public Broomstick(int wheels, int production_year, String brand, int max_speed) {
        super(wheels, production_year, brand);
        this.max_speed = max_speed;
    }

    @Override
    public String toString() {
        String s = super.toString();
        s.replace("]", (", max_speed=" + max_speed + "]"));
        return s;
    }

    public static void saveObject(Broomstick obj, String file) {
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

    public static Broomstick readObject(String file) {
        try {
            FileInputStream fis = new FileInputStream(file);
            ObjectInputStream ois = new ObjectInputStream(fis);

            Broomstick obj = (Broomstick) ois.readObject();
            fis.close();
            ois.close();
            return obj;
        } catch (FileNotFoundException e) {
            return new Broomstick();
        } catch (IOException e) {
            System.out.println("cant read object");
        } catch (ClassNotFoundException e) {
            System.out.println("Broomstick not found");
        }
        return null;
    }

    public void editor(String file) {
        BroomstickEdit editor = new BroomstickEdit(this, file);
        editor.run();
    }
}
