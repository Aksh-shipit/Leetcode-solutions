SELECT w1.id
FROM WEATHER w1
JOIN WEATHER w2
ON DATEDIFF(w1.recordDate,w2.recordDate)=1
WHERE w1.temperature>w2.temperature;