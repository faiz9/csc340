public class MyFavoriteApp <T>{

    //private String name;

    private T object;

    public void setObject(T t){
        this.object = t;
    }

    public void print(){
        System.out.println(object);
    }

    public static void main(String[] args){
        sayStuff(10);
        sayStuff("World");

        MyFavoriteApp<String> test1 = new MyFavoriteApp<>();
        MyFavoriteApp<Integer> test2 = new MyFavoriteApp<>();
        test1.setObject("Hello");
        test1.print();

        test2.setObject(10);
        test2.print();

        //test1.setObject(12); compiler errors
        subtypeTest(new ClassA());
        subtypeTest(new ClassB());
    }

    static void subtypeTest(ClassA a){
    }

    static void sayStuff(int a){
        System.out.println("Hello : " + a);
    }

    static void sayStuff(String b){
        System.out.println("Hello : " + b);
    }
}
