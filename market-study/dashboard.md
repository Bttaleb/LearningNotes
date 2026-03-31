# Dashboard

## Recent Studies
```dataview
TABLE date, pair, outcome, tags
FROM "studies"
SORT date DESC
LIMIT 20
```

## CISD Studies
```dataview
TABLE date, pair, cisd_type, outcome
FROM "studies/key-levels"
SORT date DESC
```

## Candle Profile Studies
```dataview
TABLE date, pair, htf_timeframe, po3_phase
FROM "studies/candle-profiles"
SORT date DESC
```

## Stats
```dataview
TABLE length(rows) as "Count"
FROM "studies"
GROUP BY outcome
```
