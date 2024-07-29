`Nowa odsłona firmware'u dla sterwoników nawadniania w wersjach 4.2 i 5.x`

## `24.07.29`

```
Po aktualizacji pojwi się "konflikt kanałów". Wymagane będzie usunięcie urządzenia z Cloud do ponownej rejestracji !!!
```

- **core**

  dodana funkcja drugiego cyklu

  dodane opóźnienie wyłączenia przekaźnika "master" po zakończeniu dowolnej sekcji, bądź po zakończeniu cyklu

- **aktualizacja biblioteki**

- **crontab**

  dodanie harmonogramu DLA drugiego cyklu

## `24.05.25`

- **podlewa.cz / crontab**

  zmiana statusu na "odblokowany", kiedy sterownik utracił połączenie z serwerem a nadszedł czas uruchomienia cyklu z wewnętrznego harmonogramu

## `24.04.28`

- **aktualizacja biblioteki**

- **flow meter**:

  dodany w konfiguracji wybór `LOW / HIGH` - ustawiamy *LOW*, kiedy zwieramy wejście **S3** do GND, a kiedy na wejście **S3** podawany jest potencjał np. 5V, ustawiamy *HIGH*

- **podlewa.cz**

  dodany status (brak połączenia z serwisem, błędy url, przekroczona ilość zapytań) sygnalizowany pomarańczowym kolorem piątej diody RGB