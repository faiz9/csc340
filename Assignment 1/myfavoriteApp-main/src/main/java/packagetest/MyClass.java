package packagetest;

public class MyClass {

    public static int a;
    static int b;
    protected static int c;
    private static int d;

    //public class MyOtherClass {
        public static void main(String args[]){
            System.out.println(MyClass.a); // works because public
            //works because in same package/class
            System.out.println(MyClass.b);
            System.out.println(MyClass.c);
            System.out.println(MyClass.d);
        }
    }
