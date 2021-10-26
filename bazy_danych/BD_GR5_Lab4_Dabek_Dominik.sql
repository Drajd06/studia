-- zadanie 2.

SELECT nr_rejestracyjny, marka, modell, data_produkcji, wlasciciel, data_up, data_up - data_produkcji as Dni, 
ROUND(MONTHS_BETWEEN(data_up,data_produkcji)/12,0) as Lat FROM POJAZDY
JOIN WLASCICIELE USING(id_wlasciciela) WHERE data_produkcji < data_up AND status_wlasciciela='osobafizyczna'
ORDER BY Dni DESC;

-- zadanie 8.

SELECT id_wedkarza, nazwisko, id_okregu, id_licencji, od_dnia || '-' || rok,  do_dnia || '-' || rok, dzienna_oplata, 
(TO_DATE(do_dnia || '-' || rok,'dd-mm-yyyy')-TO_DATE(od_dnia || '-' || rok,'dd-mm-yyyy')+1)*dzienna_oplata AS stawka
FROM licencje JOIN wedkarze USING(id_wedkarza) JOIN oplaty USING(rok,id_okregu)
WHERE NOT(od_dnia like '01-01' AND do_dnia like '31-12');

-- zadanie 10.

SELECT p1.nr_akt, p1.nazwisko, p1.imiona, DECODE(p2.nr_akt,null,'Brak',p2.nr_akt) przelozony, 
p2.nazwisko || ' ' || p2.imiona szef FROM pracownicy p1 
LEFT JOIN pracownicy p2 ON (p1.przelozony=p2.nr_akt);

-- zadanie 11.

SELECT COUNT(*) ilosc, rok, gr_dziekan FROM studenci WHERE kierunek LIKE 'INFORMATYKA'
GROUP BY rok, gr_dziekan HAVING count(*) BETWEEN 10 AND 13;

-- zadanie 14.

SELECT kierunek, rok, min(data_urodzenia), max(data_urodzenia), 
MONTHS_BETWEEN(max(data_urodzenia),min(data_urodzenia)) FROM studenci
WHERE stopien=1  AND tryb='STACJONARNY' GROUP BY kierunek, rok HAVING MONTHS_BETWEEN(max(data_urodzenia),min(data_urodzenia))>=100
ORDER BY 4 DESC;

-- zadanie 19.

SELECT stanowisko, COUNT(nr_akt), NVL(AVG(placa),0), MIN(placa), MAX(placa) FROM PRACOWNICY RIGHT JOIN STANOWISKA USING(stanowisko)
WHERE data_zwol IS NULL OR data_zwol>=SYSDATE GROUP BY stanowisko ORDER BY 2 DESC, 3 DESC;

-- zadanie 23.

SELECT nr_indeksu, nazwisko, imiona, COUNT(*) FROM OCENY JOIN STUDENCI USING(nr_indeksu) 
WHERE ocena IS NULL GROUP BY nr_indeksu, nazwisko, imiona HAVING COUNT(*)>=2;

SELECT nr_indeksu, nazwisko, imiona, COUNT(*)-COUNT(OCENA) FROM OCENY JOIN STUDENCI USING(nr_indeksu) 
GROUP BY nr_indeksu, nazwisko, imiona HAVING COUNT(*)-COUNT(OCENA)>=2 AND COUNT(OCENA) BETWEEN 10 AND 20;