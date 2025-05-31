import signaltools


class SignalType(enum.Enum):
    Sine = "sin"
    Cosine = "cos"
    Square = "square"
    Sawtooth = "saw"


def generate_signal(signal_type: SignalType, frequency: float, sampling_rate: float, duration: float):
    if signal_type == SignalType.Sine:
        return signaltools.generate_sine(frequency, sampling_rate, duration)
    elif signal_type == SignalType.Cosine:
        return signaltools.generate_cosine(frequency, sampling_rate, duration)
    elif signal_type == SignalType.Square:
        return signaltools.generate_square(frequency, sampling_rate, duration)
    elif signal_type == SignalType.Sawtooth:
        return signaltools.generate_sawtooth(frequency, sampling_rate, duration)
    else:
        raise ValueError("Unsupported signal type")


def DFT(signal, sampling_rate: float, show_plot=False):
    dft = signaltools.compute_dft(signal)
    if show_plot:
        from matplotlib import pyplot as plt
        magnitude = np.abs(dft)
        freq = np.linspace(0, sampling_rate, len(dft))
        plt.plot(freq, magnitude)
        plt.title("DFT Spectrum")
        plt.xlabel("Frequency [Hz]")
        plt.ylabel("Magnitude")
        plt.grid(True)
        plt.show()
    return dft


def FFT(signal, sampling_rate: float, show_plot=False):
    return DFT(signal, sampling_rate, show_plot)


def showSignal(x, y):
    from matplotlib import pyplot as plt
    plt.plot(x, y)
    plt.title("Signal")
    plt.xlabel("Time [s]")
    plt.ylabel("Amplitude")
    plt.grid(True)
    plt.show()


def showSimpleSignal(y, sampling_rate):
    x = [i / sampling_rate for i in range(len(y))]
    showSignal(x, y)
