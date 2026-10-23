import java.util.Stack;

public class History {
    private final Stack<Memento> mementos = new Stack<>();

    public void push(Memento memento) {
        mementos.push(memento);
    }

    public Memento pop() {
        return mementos.pop();
    }
}
