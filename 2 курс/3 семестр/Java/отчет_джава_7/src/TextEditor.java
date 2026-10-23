public class TextEditor {
    private String text = "";

    public void setText(String text) {
        this.text = text;
    }

    public String getText() {
        return text;
    }

    // создать снимок состояния
    public Memento save() {
        return new Memento(text);
    }

    // восстановить состояние из снимка
    public void restore(Memento memento) {
        this.text = memento.getText();
    }
}
