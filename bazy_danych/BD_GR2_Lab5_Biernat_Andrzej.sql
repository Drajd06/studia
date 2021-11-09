--zad1
select * from Studenci where imiona like '%a' and kierunek like 'INFORMATYKA'
and data_urodzenia=(select max(data_urodzenia) from Studenci where imiona like '%a' and kierunek like 'INFORMATYKA');

--zad4
select kierunek, tryb, srednia, nr_indeksu
from studenci where (kierunek, tryb, srednia) in
    (select kierunek, tryb, max(srednia) from Studenci
    where rok = 2 group by tryb, kierunek)
order by 1, 2;

select * from
(select kierunek, tryb, srednia, nr_indeksu from studenci)t1 join
(select kierunek, tryb, max(srednia) max_srednia from Studenci
group by tryb, kierunek)t2
on (t1.kierunek=t2.kierunek and t1.tryb=t2.tryb and max_srednia=srednia);

--zad12
select * from (
select id_dzialu, nr_akt, nazwisko, data_zatr from pracownicy
join dzialy using(id_dzialu)
where (data_zwol is null or data_zwol >= sysdate)) t1 Join
(select id_dzialu, min(data_zatr) najstarszy, max(data_zatr) najmlodszy from pracownicy
where data_zwol is null or data_zwol >= sysdate group by id_dzialu) t2
on (t1.id_dzialu=t2.id_dzialu and (data_zatr=najstarszy or data_zatr=najmlodszy))
order by t1.id_dzialu;

--zadanie dodatkowe
/*
wyswietl wedkarzy, którzy w danym roku kalendarzowym bywali czêœciej na rybach
ni¿ wynosi œrednia przypadajaca na wedkarza
*/
select * from

(select id_wedkarza, nazwisko, extract(year from czas) rok, count(*) liczba
from rejestry join wedkarze using(id_wedkarza)
group by id_wedkarza, nazwisko, extract(year from czas)) t1 join(

select extract(year from czas) rok, count(*)/count(distinct id_wedkarza) srednia
from rejestry group by extract(year from czas)) t2 on (t1.rok=t2.rok and liczba>srednia)

order by t1.rok, id_wedkarza;

--zad20
select to_char(czas, 'day') dzien, lw.nazwa lowisko, ga.nazwa gatunek,
count(re.id_gatunku), sum(waga), count(distinct id_wedkarza),
GROUPING_ID(to_char(czas, 'day'), lw.nazwa, ga.nazwa) numer
from rejestry re
join lowiska lw on (re.id_lowiska=lw.id_lowiska)
join gatunki ga on (re.id_gatunku=re.id_gatunku)
group by rollup (to_char(czas, 'day'), lw.nazwa, ga.nazwa);

select to_char(czas, 'day') dzien, lw.nazwa lowisko, ga.nazwa gatunek,
count(re.id_gatunku), sum(waga), count(distinct id_wedkarza),
GROUPING_ID(to_char(czas, 'day'), lw.nazwa, ga.nazwa) numer
from rejestry re
join lowiska lw on (re.id_lowiska=lw.id_lowiska)
join gatunki ga on (re.id_gatunku=re.id_gatunku)
group by cube (to_char(czas, 'day'), lw.nazwa, ga.nazwa);

select decode(grouping (to_char(czas, 'day')), 1, 'Podsumowanie', to_char(czas, 'day')) dzien, lw.nazwa lowisko, ga.nazwa gatunek,
count(re.id_gatunku), sum(waga), count(distinct id_wedkarza),
GROUPING_ID(to_char(czas, 'day'), lw.nazwa, ga.nazwa) numer
from rejestry re
join lowiska lw on (re.id_lowiska=lw.id_lowiska)
join gatunki ga on (re.id_gatunku=re.id_gatunku)
group by grouping sets
((to_char(czas, 'day'), lw.nazwa, ga.nazwa),(to_char(czas, 'day'), ga.nazwa),
(lw.nazwa, ga.nazwa), ga.nazwa, ());





--zad3

select * from lowiska;

/*select waga,nazwa,lowisko,imiona,dzien from 
(select id_wedkarza, id_lowiska,id_gatunku,
NVL((select nazwa from lowiska where id_wedkarza=we.id_wedkarza),0) lowisko,
NVL((select nazwisko from wedkarze where id_lowiska=we.id_lowiska),0) nazwisko,
NVL((select nazwa from gatunki where id_gatunku=we.id_gatunku),0) nazwa,
NVL((select imiona from wedkarze where id_wedkarza=we.id_wedkarza),0) from rejestry we
);
*/
select * from rejestry join wedkarze using (id_wedkarza) where trim(to_char(czas,'day'))
in ('sobota', 'niedziela') and extract(month from czas)=5 and waga=4.1;

select max(waga) from rejestry where trim(to_char(czas,'day'))
in ('sobota', 'niedziela') and extract(month from czas)=5;


--dodatek

select nr_indeksu, nazwisko,
(select count(*) from oceny where ocena=5 and nr_indeksu=st.nr_indeksu) Liczba_5,
(select count(*) from oceny where ocena=4 and nr_indeksu=st.nr_indeksu) Liczba_4,
(select count(*) from oceny where ocena=3 and nr_indeksu=st.nr_indeksu) Liczba_3

from studenci st;


--zad 8,9

--przy tablicy


--zad 17

select decode(grouping(tryb),1,'podsumowanie',tryb) tryb, stopien, kierunek, rok, count(*), grouping_id(tryb, stopien, kierunek, rok)
nr from studenci
group by rollup (tryb, stopien, kierunek, rok)
;

select decode(grouping(tryb),1,'podsumowanie',tryb) tryb, stopien, kierunek, rok, count(*), grouping_id(tryb, stopien, kierunek, rok)
nr from studenci
group by cube(tryb, stopien, kierunek, rok)
;

select decode(grouping(tryb),1,'podsumowanie',tryb) tryb, stopien, kierunek, rok, count(*), grouping_id(tryb, stopien, kierunek, rok)
nr from studenci
group by grouping sets((tryb, stopien, kierunek, rok),(tryb, stopien, kierunek),
(tryb, stopien),(tryb),())
;

