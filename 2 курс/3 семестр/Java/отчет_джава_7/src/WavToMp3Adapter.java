public class WavToMp3Adapter implements MediaPlayer {
    private final WavPlayer wavPlayer;

    public WavToMp3Adapter(WavPlayer wavPlayer) {
        this.wavPlayer = wavPlayer;
    }

    @Override
    public void play() {
        System.out.println("Адаптер преобразует WAV в интерфейс MediaPlayer");
        wavPlayer.playWav();
    }
}
