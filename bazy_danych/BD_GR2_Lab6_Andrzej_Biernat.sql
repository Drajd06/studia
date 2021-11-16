--zadanie 1
select to_char(czas,'yyyy-mm-dd hh24:mi') czas, dlugosc, 'wieksze' opis
from rejestry
where id_gatunku = 9 and dlugosc > 58
union
select to_char(czas,'yyyy-mm-dd hh24:mi') czas, dlugosc, 'Rowna sredniej'
from rejestry
where id_gatunku = 9 and dlugosc = 58
union
select to_char(czas,'yyyy-mm-dd hh24:mi') czas, dlugosc, 'mniejsze'
from rejestry
where id_gatunku = 9 and dlugosc < 58
order by czas;

--zadanie 3
select t1.id_gatunku, nazwa, count(re.id_gatunku) from (
select id_gatunku, nazwa from gatunki
minus
select id_gatunku, nazwa
from rejestry join gatunki using (id_gatunku)
group by id_gatunku, nazwa having count(*) > 7
) t1 left join rejestry re on (t1.id_gatunku=re.id_gatunku)
group by t1.id_gatunku, t1.nazwa;

--zadanie 12
select rok, id_okregu, sum(roczna_oplata_pod) kwota, count(*) liczba_licencji, 'rocznepod'
from licencje join oplaty using(rok, id_okregu) where id_okregu like 'PZW%'
and rodzaj='podstawowa'
group by rok, id_okregu

union

select rok, id_okregu, sum(roczna_oplata_dod) kwota, count(*) liczba_licencji, 'rocznedod'
from licencje join oplaty using(rok, id_okregu) where id_okregu like 'PZW%'
and rodzaj='dodatkowa' and od_dnia = '01-01' and do_dnia = '31-12'
group by rok, id_okregu

union

select rok, id_okregu,
sum(
    (to_date(do_dnia || '-' || rok, 'dd-mm-yyyy') - to_date(od_dnia || '-' || rok, 'dd-mm-yyyy') + 1)
    * dzienna_oplata
) kwota,
count(*) liczba_licencji, 'dzienne'
from licencje join oplaty using(rok, id_okregu) where id_okregu like 'PZW%'
and rodzaj='dodatkowa' and not (od_dnia = '01-01' and do_dnia = '31-12')
group by rok, id_okregu
order by 1, 2;

--zadanie 15
select id_gatunku, nazwa,
    case
        (select count (DISTINCT id_gatunku) from rejestry
        join lowiska using (id_lowiska)
        where id_gatunku = ga.id_gatunku and id_okregu like 'PZW%'
        )
    when 0 then 'niezlowiona'
    when 1 then '1 okreg'
    when 2 then '2 okregi'
    when 3 then '3 okregi'
    else 'powyzej 3 okregow'
    end opis
from gatunki ga;
