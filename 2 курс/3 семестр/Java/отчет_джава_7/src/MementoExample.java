public class MementoExample {
    public static void main(String[] args) {
        TextEditor editor = new TextEditor();
        History history = new History();

        editor.setText("Привет");
        history.push(editor.save());

        editor.setText("Привет, мир");
        history.push(editor.save());

        editor.setText("Привет, мир!!!");
        System.out.println("Текущий текст: " + editor.getText());

        editor.restore(history.pop());
        System.out.println("После первого восстановления: " + editor.getText());

        editor.restore(history.pop());
        System.out.println("После второго восстановления: " + editor.getText());
    }
}
