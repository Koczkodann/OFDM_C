###Biblioteka FileControl
Funkcja checkFileLength
Funkcja ta sprawdza długość pliku tekstowego, mierzoną liczbą znaków.

Parametry:
filename: Ścieżka do pliku tekstowego, którego długość ma być sprawdzana.
Zwracana wartość: Liczba całkowita reprezentująca ilość znaków w pliku.

Opis:
Funkcja otwiera podany plik w trybie do odczytu, a następnie zlicza ilość znaków, ignorując białe znaki, do momentu osiągnięcia końca pliku (EOF). W przypadku problemów z otwarciem pliku, funkcja wyświetla komunikat o błędzie na standardowym wyjściu błędów.

Funkcja checkFileLengthLine
Funkcja ta sprawdza ilość linii w pliku tekstowym.

Parametry:
filename: Ścieżka do pliku tekstowego, którego ilość linii ma być sprawdzana.
Zwracana wartość: Liczba całkowita reprezentująca ilość linii w pliku.

Opis:
Funkcja otwiera podany plik w trybie do odczytu, a następnie zlicza ilość linii, do momentu osiągnięcia końca pliku (EOF). W przypadku problemów z otwarciem pliku, funkcja wyświetla komunikat o błędzie na standardowym wyjściu błędów.

Funkcja loadFileBin
Funkcja wczytuje dane binarne z pliku tekstowego do tablicy liczb zmiennoprzecinkowych.

Parametry:
output: Tablica liczb zmiennoprzecinkowych, do której wczytane będą dane z pliku.
filename: Ścieżka do pliku tekstowego, z którego dane mają być wczytywane.

Opis:
Funkcja otwiera podany plik w trybie do odczytu, a następnie wczytuje dane, interpretując je jako liczby całkowite i zapisuje do tablicy output. W przypadku problemów z otwarciem pliku, funkcja wyświetla komunikat o błędzie na standardowym wyjściu błędów.

Funkcja loadFileCpx
Funkcja wczytuje liczby zespolone z pliku tekstowego do tablicy struktur kiss_fft_cpx.

Parametry:
input: Tablica struktur kiss_fft_cpx, do której wczytywane będą liczby zespolone z pliku.
filename: Ścieżka do pliku tekstowego, z którego dane mają być wczytywane.

Opis:
Funkcja otwiera podany plik w trybie do odczytu, a następnie wczytuje dane z każdej linii, interpretując je jako liczby zespolone i zapisuje do tablicy input. W przypadku problemów z otwarciem pliku lub błędów w parsowaniu linii, funkcja wyświetla odpowiednie komunikaty na standardowym wyjściu błędów.

Funkcja saveFile
Funkcja zapisuje dane liczbowe zespolone do pliku tekstowego.

Parametry:
input: Dwuwymiarowa tablica struktur kiss_fft_cpx, zawierająca dane liczbowe zespolone.
filename: Ścieżka do pliku tekstowego, do którego dane mają być zapisywane.
packetsNum: Liczba pakietów danych.
length: Długość każdego pakietu danych.

Opis:
Funkcja otwiera podany plik w trybie do zapisu, a następnie iteruje przez tablicę dwuwymiarową input i zapisuje dane liczbowe zespolone do pliku w formie tekstowej. W przypadku problemów z otwarciem pliku, funkcja wyświetla komunikat o błędzie na standardowym wyjściu błędów.

Funkcja saveFileBin
Funkcja zapisuje dane liczbowe zmiennoprzecinkowe do pliku tekstowego w formie binarnej.

Parametry:
input: Jednowymiarowa tablica liczb zmiennoprzecinkowych, zawierająca dane do zapisu.
filename: Ścieżka do pliku tekstowego, do którego dane mają być zapisywane.
packetsNum: Liczba pakietów danych.
length: Długość każdego pakietu danych.

Opis:
Funkcja otwiera podany plik w trybie do zapisu, a następnie iteruje przez jednowymiarową tablicę input i zapisuje dane liczbowe zmiennoprzecinkowe do pliku w formie binarnej. W przypadku problemów z otwarciem pliku, funkcja wyświetla komunikat o błędzie na standardowym wyjściu błędów.


###Biblioteka QAM
Funkcja bpskModulation
Funkcja wykonuje modulację sygnału binarnego w schemacie BPSK (Binary Phase Shift Keying).

Parametry:
nBits: Ilość bitów na symbol (w tym przypadku zawsze 1 dla BPSK).
input: Tablica wejściowa zawierająca sygnał binarny do zmodulowania.
output: Tablica wyjściowa przechowująca zmodulowany sygnał.
inputNum: Liczba elementów w tablicy wejściowej.

Opis:
Funkcja iteruje przez tablicę wejściową i przekształca każdy bit na symbol BPSK, gdzie wartość 0 jest mapowana na -1, a wartość 1 na 1. Wynik jest zapisywany w tablicy wyjściowej.

Funkcja bpskDemodulation
Funkcja wykonuje demodulację sygnału BPSK, przekształcając go z powrotem na sygnał binarny.

Parametry:
nBits: Ilość bitów na symbol (w tym przypadku zawsze 1 dla BPSK).
input: Tablica wejściowa zawierająca zmodulowany sygnał do demodulacji.
output: Tablica wyjściowa przechowująca zdemodulowany sygnał binarny.
inputNum: Liczba elementów w tablicy wejściowej.

Opis:
Funkcja iteruje przez tablicę wejściową i przekształca każdy symbol BPSK na bit, gdzie wartość -1 jest mapowana na 0, a wartość 1 na 1. Wynik jest zapisywany w tablicy wyjściowej.


###Biblioteka ModMat
Funkcja fftShift
Funkcja przesuwa część widma sygnału FFT w celu uzyskania symetrii, co ułatwia interpretację wyników.

Parametry:
input: Dwuwymiarowa tablica struktur kiss_fft_cpx reprezentująca wynik transformacji FFT.
size1: Rozmiar pierwszego wymiaru tablicy input.
size2: Rozmiar drugiego wymiaru tablicy input.

Opis:
Funkcja tworzy tymczasową tablicę temp, przesuwa wartości wzdłuż drugiego wymiaru o połowę (shift), a następnie aktualizuje oryginalną tablicę input o nowe wartości z tablicy temp. Proces ten jest powtarzany dla wszystkich wierszy tablicy input.

Funkcja zeros
Funkcja dodaje zerowe elementy na początku każdego wiersza dwuwymiarowej tablicy input.

Parametry:
input: Dwuwymiarowa tablica struktur kiss_fft_cpx reprezentująca wejściowe dane do przekształcenia.
output: Dwuwymiarowa tablica struktur kiss_fft_cpx reprezentująca dane po dodaniu zer.
size1: Rozmiar pierwszego wymiaru tablicy input.
size2: Rozmiar drugiego wymiaru tablicy input.
nZeros: Liczba zerowych elementów dodawanych na początku każdego wiersza.

Opis:
Funkcja inicjalizuje zerami odpowiednią liczbę elementów na początku każdego wiersza tablicy output, a następnie kopiuję elementy z tablicy input przesuwając się w drugim wymiarze o liczbę zer nZeros.

Funkcja rmZeros
Funkcja usuwa określoną liczbę zerowych elementów z początku każdego wiersza dwuwymiarowej tablicy input.

Parametry:
input: Dwuwymiarowa tablica struktur kiss_fft_cpx reprezentująca dane wejściowe z zerami na początku.
output: Dwuwymiarowa tablica struktur kiss_fft_cpx reprezentująca dane po usunięciu zer.
size1: Rozmiar pierwszego wymiaru tablicy input.
size2: Rozmiar drugiego wymiaru tablicy input.
nZeros: Liczba zerowych elementów usuwanych z początku każdego wiersza.

Opis:
Funkcja kopiuję elementy z tablicy input, pomijając pierwsze nZeros elementów każdego wiersza, do tablicy output.

###Biblioteka kissFFT
Biblioteka kissfft to otwarta biblioteka C dla szybkich transformat Fouriera (FFT). Jej głównym celem jest dostarczenie prostego, wydajnego i przenośnego rozwiązania do obliczeń FFT.
Transformata 1D (kiss_fft)
Biblioteka kissfft oferuje efektywną implementację transformaty Fouriera (FFT). Funkcje takie jak kiss_fft_alloc i kiss_fft umożliwiają użytkownikowi przeprowadzenie transformacji na danych wejściowych, zwracając wyniki w formie liczbowych wartości zespolonych. Transformata ta jest użyteczna w wielu dziedzinach, takich jak przetwarzanie sygnałów, komunikacja cyfrowa czy analiza widma.
Struktura kiss_fft_cpx
W ramach biblioteki kissfft, struktura kiss_fft_cpx jest wykorzystywana do reprezentacji liczbowych wartości zespolonych. Składa się z dwóch pól ‘.r’ (część rzeczywista) ‘.i’ (część urojona). Ta prosta struktura umożliwia przechowywanie wyników transformaty Fouriera w formie skojarzonych par liczb zespolonych.
