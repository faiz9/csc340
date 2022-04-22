package packagetest;

public class MyOtherClass {

    public static void main(String args[]){
        System.out.println(MyClass.a); // works because public
        //works because in same package/class
        System.out.println(MyClass.b);
        System.out.println(MyClass.c);
        //private access only works within same class
        //System.out.println(MyClass.d);
    }
}
