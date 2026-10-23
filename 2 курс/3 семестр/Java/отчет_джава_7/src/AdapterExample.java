public class AdapterExample {
    public static void main(String[] args) {
        MediaPlayer mp3 = new Mp3Player("song.mp3");
        MediaPlayer wav = new WavToMp3Adapter(new WavPlayer("sound.wav"));

        mp3.play();
        wav.play();
    }
}
