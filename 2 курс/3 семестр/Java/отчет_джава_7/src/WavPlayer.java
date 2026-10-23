public class WavPlayer {
    private final String fileName;

    public WavPlayer(String fileName) {
        this.fileName = fileName;
    }

    public void playWav() {
        System.out.println("Воспроизведение WAV: " + fileName);
    }
}
