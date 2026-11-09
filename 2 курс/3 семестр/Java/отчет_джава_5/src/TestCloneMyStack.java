public class TestCloneMyStack {
    public static void main(String[] args) {
        MyStack stack1 = new MyStack();
        stack1.push("Первый");
        stack1.push("Второй");
        MyStack stack2 = (MyStack) stack1.clone();
        stack2.push("Третий");

        System.out.println("Оригинал (stack1): " + stack1);
        System.out.println("Клон (stack2):     " + stack2);
    }
}
