public class StackOnQueueTest {
    public static void main(String[] args) {
        StackOnQueue stack = new StackOnQueue();

        stack.push(10);
        stack.push(20);

        System.out.println("Вершина стека: " + stack.top());
        System.out.println("Удален элемент: " + stack.pop());
        System.out.println("Стек пуст: " + stack.empty());
        System.out.println("Элементы стека: " + stack);
    }
}
