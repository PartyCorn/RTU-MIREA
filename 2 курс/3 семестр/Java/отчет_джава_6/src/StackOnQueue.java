import java.util.LinkedList;
import java.util.Queue;

public class StackOnQueue {
    private Queue<Integer> q1 = new LinkedList<>();
    private Queue<Integer> q2 = new LinkedList<>();

    // положить элемент на вершину
    public void push(int x) {
        q2.add(x);
        while (!q1.isEmpty()) {
            q2.add(q1.poll());
        }
        // меняем очереди местами
        Queue<Integer> tmp = q1;
        q1 = q2;
        q2 = tmp;
    }

    // удалить элемент с вершины и вернуть его
    public int pop() {
        if (q1.isEmpty()) {
            throw new RuntimeException("Стек пуст");
        }
        return q1.poll();
    }

    // посмотреть вершину без удаления
    public int top() {
        if (q1.isEmpty()) {
            throw new RuntimeException("Стек пуст");
        }
        return q1.peek();
    }

    // проверка на пустоту
    public boolean empty() {
        return q1.isEmpty();
    }

    // строка со всеми элементами (вершина первая)
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        int n = q1.size();
        for (int i = 0; i < n; i++) {
            int x = q1.poll();
            sb.append(x);
            if (i < n - 1) {
                sb.append(", ");
            }
            q1.add(x);
        }
        return sb.append("]").toString();
    }
}
