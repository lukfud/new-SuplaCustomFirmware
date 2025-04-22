`Nowa odsłona firmware'u dla sterwoników nawadniania w wersjach 4.2 i 5.x`

## `25.04.21`

- **core**

  dodana możliwość dowolnego dodawania sekcji do grup (cykl 1 i 2) - po aktualizacji należy je ustawić np.: 1,2,3,5,8
  
  dropbne poprawki
  
- **aktualizacja bibliotek**

## `24.10.15`

- **core**

  dodana w konfiguracji opcja umożliwiająca wybranie dla której grupy (cykl 1 i 2) ma się włączać master
  
  dodana funkcja dolewu wody. Po włączeniu w konfiguracji, ostatni (bądż przedostatni, kiedy włączony jest master) przekaźnik włacza/wyłącza się w zależności od stanu czujnika S5
  
  dodane powiadomienie o zużyciu wody po zakończeniu cyklu. Konieczne jest wpisanie w konfiguracji ilości impulsów na litr wody
  
  drobne poprawki
  
- **aktualizacja biblioteki**

## `24.09.10`

```
Po aktualizacji domyślnie czujnik deszczu będzie wyłączony
```

- **core**

  dodana w konfiguracji opcja włączenia/wyłączenia fizycznego czujnika deszczu
  
- **aktualizacja biblioteki**

## `24.08.05`

- **core**

  dodana możliwość manualnej korekty czasu sekcji w zakresie 10 - 100%. Po włączeniu opcji w konfiguracji pojawi się kanał ściemniacza, który należy włączyć i ustawić żądany %. Po zakończeniu podlewania ściemniacz automatycznie się wyłączy

## `24.07.31`

- **core**

  dodane pominięcie sekcji w cyklach, aby pominąć sekcję należy ustawić jej czas na 0,5 s
  
  drobne poprawki

## `24.07.29`

```
Po aktualizacji pojwi się "konflikt kanałów". Wymagane będzie usunięcie urządzenia z Cloud do ponownej rejestracji !!!
```

- **core**

  dodana funkcja drugiego cyklu

  dodane opóźnienie wyłączenia przekaźnika "master" po zakończeniu dowolnej sekcji, bądź po zakończeniu cyklu

- **aktualizacja biblioteki**

- **crontab**

  dodany harmonogram dla drugiego cyklu

## `24.05.25`

- **podlewa.cz / crontab**

  zmiana statusu na "odblokowany", kiedy sterownik utracił połączenie z serwerem a nadszedł czas uruchomienia cyklu z wewnętrznego harmonogramu

## `24.04.28`

- **aktualizacja biblioteki**

- **flow meter**:

  dodany w konfiguracji wybór `LOW / HIGH` - ustawiamy *LOW*, kiedy zwieramy wejście **S3** do GND, a kiedy na wejście **S3** podawany jest potencjał np. 5V, ustawiamy *HIGH*

- **podlewa.cz**

  dodany status (brak połączenia z serwisem, błędy url, przekroczona ilość zapytań) sygnalizowany pomarańczowym kolorem piątej diody RGB
