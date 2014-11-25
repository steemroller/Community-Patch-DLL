-- Extra Spies based on # of Minors

INSERT INTO Defines (
Name, Value)
SELECT 'BALANCE_SPY_TO_MINOR_RATIO', '15'
WHERE EXISTS (SELECT * FROM COMMUNITY WHERE Type='COMMUNITY_CORE_BALANCE_BUILDINGS' AND Value= 1 );