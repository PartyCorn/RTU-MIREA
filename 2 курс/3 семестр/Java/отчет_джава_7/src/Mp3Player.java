public class Mp3Player implements MediaPlayer {
    private final String fileName;

    public Mp3Player(String fileName) {
        this.fileName = fileName;
    }

    @Override
    public void play() {
        System.out.println("Воспроизведение MP3: " + fileName);
    }
}
