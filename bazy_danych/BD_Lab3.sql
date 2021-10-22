--zadanie 1
select nazwisko, stanowisko, placa,
placa - 5411.45 as Odchylenie,
trunc(placa - 5411.45, 1) as "Trunc do 0.1",
round(placa - 5411.45, -2) as "Round do 100-ek"
from pracownicy;

--zadanie2
select nazwisko, stanowisko,
placa/1.17 as "Placa netto",
round(placa/1.17, -2) as "Placa zaokraglona",
round(placa/1.17, -2) - trunc(placa/1.17, -2) as "Roznica Round-Trunc"
from pracownicy;

--zadanie3


    --zadanie4
select
interval '101-11' year(3) to month as "Przedzial A 101 lat 11 m",
interval '25 03:05:36.6' day(2) to second as "Przedzia B"
from dual;

--zadanie5
select
sysdate + 4321 as "Za 4321",
sysdate - 4321 as "przeszlosc",
trunc(((sysdate + 4321) - (sysdate - 4321))/7) as tygodni,
trunc(months_between(sysdate + 4321,sysdate - 4321)) as miesiecy
from dual;

--zadanie6
select
Systimestamp as "aktualny czas",
Systimestamp - interval '1234' day(4) - interval '18' hour(2) as przeszlosc, 
systimestamp + interval '189-5' year(3) to month as przyszlosc
from dual;

--zadanie7
select
TO_TIMESTAMP('2021-02-11 7:17', 'yyyy-mm-dd hh24:mi:ss') - TO_TIMESTAMP('2013-12-15 21:14:09', 'yyyy-mm-dd hh24:mi:ss') as "Roznica w dniach",
(TO_TIMESTAMP('2021-02-11 7:17', 'yyyy-mm-dd hh24:mi:ss') - TO_TIMESTAMP('2013-12-15 21:14:09', 'yyyy-mm-dd hh24:mi:ss')) / 365.25 as "Roznica w lata-miesiace"
from dual;

--zadanie10
select
add_months(sysdate, 123) || ', ' || to_char(sysdate, 'WW') || ' tydzien'
from dual;

--zadanie11
select
last_day(sysdate) || ', ' || to_char(last_day(sysdate), 'Day')
from dual;

--zadanie12
select
sysdate as aktualnie,
round(sysdate, 'MM') as miesiecy,
trunc(sysdate) as lat,
round(sysdate, 'CC') as wiekow
from dual;

--zadanie13
select nazwisko, imiona, data_urodzenia,
trunc((sysdate - data_urodzenia)/365.25) as "pelne lata",
extract(year from sysdate) - extract(year from data_urodzenia) as "test"
from studenci
where imiona like 'M%'
order by data_urodzenia;

--zadanie14
select
Systimestamp as "aktualny czas",
cast(Systimestamp as date) as "data"
from dual;

--zadanie15
select
concat('987', '654') as lancuch,
to_number('987654') as liczba,
to_number('987654') - 123456 as roznica
from dual;

--zadanie16
select
to_char(to_char(sysdate, 'CC'), 'RN') as "wiek rzymski"
from dual;

--zadanie17
select
'czeœæ, jest dzisaj ' || to_char(sysdate, 'Day') || ', ' ||
extract(day from sysdate) || ' ' ||
to_char(sysdate, 'Month') || ' ' || extract(year from sysdate)
from dual;

--zadanie18
select
to_char(to_date('27-09-1959', 'dd-mm-yyyy'), 'CC') || ' wiek ' ||
to_char(to_date('27-09-1959', 'dd-mm-yyyy'), 'Q') || ' kwartal ' ||
to_char(to_date('27-09-1959', 'dd-mm-yyyy'), 'Month') ||
to_char(to_date('27-09-1959', 'dd-mm-yyyy'), 'W') || ' tydzien ' ||
to_char(to_date('27-09-1959', 'dd-mm-yyyy'), 'Day')
from dual;


    --zasanie20
select nazwisko, stanowisko, data_zatr, data_zwol,
systimestamp - data_zatr as "pracuje juz"
from pracownicy
where data_zwol is null or data_zwol < systimestamp
order by nazwisko, systimestamp - data_zatr;

--zadanie21
select nazwisko, stanowisko, data_zatr, data_zwol, round(placa/12) as pensja
from pracownicy
where data_zwol >= TO_DATE('2018-06-01', 'YYYY-MM-DD') and data_zatr < TO_DATE('2018-05-01', 'YYYY-MM-DD');

--zadanie23
select imiona, nazwisko
from studenci
where length(imiona) = 5 and nazwisko like 'Ko%ski';
