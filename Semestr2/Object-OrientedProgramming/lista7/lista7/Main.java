/*
 * Borys Adamiak
 * Lista 7 PO
 * javac *.java    java Main.class Audi Car
 */

package lista7;

public class Main {
    public static void main(String args[]) {
        if (args.length < 2) {
            System.out.println("Too few args");
            return;
        }
        String file = args[0];
        String name = args[1];
        Vehicle obj;
        if (name.compareTo("Vehicle") == 0)
            obj = Vehicle.readObject(file);
        else if (name.compareTo("Car") == 0)
            obj = Car.readObject(file);
        else if (name.compareTo("Broomstick") == 0)
            obj = Broomstick.readObject(file);
        else {
            System.out.println("Class doesnt exist");
            return;
        }
        testVehicle();
        obj.editor(file);
    }
    static void testVehicle()
    {
        Car Ford = new Car();
        Car Audi = new Car(4, 2009, "Audi", "A5");
        Broomstick Nimbus = new Broomstick(0, 1985, "Nimbus", 100);
        Broomstick Firebolt = new Broomstick(0, 1990, "Firebolt", 150);
        Car.saveObject(Audi, "Audi");
        Broomstick.saveObject(Firebolt, "Firebolt");
        Audi = Car.readObject("Audi");
        Firebolt = Broomstick.readObject("Firebolt");

        System.out.println(Ford.toString());
        System.out.println(Nimbus.toString());
        System.out.println(Audi.toString());
        System.out.println(Firebolt.toString());
        
    }
}
