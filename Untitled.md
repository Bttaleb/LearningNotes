---
aliases:
---
-----

# ═══════════════════════════════════════════

# CANDLE TRADE BACKTEST JOURNAL v2

# ═══════════════════════════════════════════

# ── Core Identifiers ──

date: {{date:YYYY-MM-DD}}
pair:
backtest_id: “{{date:YYYYMMDD}}-”

# ── Candle Selection ──

trading_timeframe: # daily | weekly | monthly
candle_traded: # e.g. “Tuesday”, “Wednesday NY AM”, “Week 3”
candle_role: # what was this candle ACTUALLY doing — no assumptions

# ══════════════════════════════════════════════

# CONTEXT — describe what you OBSERVE, not what the model says “should” happen

# ══════════════════════════════════════════════

# Monthly Context (leave blank if not relevant)

monthly_bias: # bullish | bearish | unclear
current_week_number: # 1 | 2 | 3 | 4
observed_phase: # what is this week ACTUALLY doing — accumulation | manipulation | distribution | continuation | reversal | range | unclear
phase_matches_model: # true | false — did the “typical” AMD model apply here?
phase_deviation_note: # if false, what actually happened? e.g. “wk1 distributed immediately, no accumulation”

# Weekly Context (leave blank if not relevant)

weekly_bias: # bullish | bearish | unclear
observed_high_of_week: # Mon | Tue | Wed | Thu | Fri | pending
observed_low_of_week: # Mon | Tue | Wed | Thu | Fri | pending
manipulation_day: # which day faked out (if any)
expansion_day: # which day delivered the real move (if any)
day_model_matched: # true | false — did Tue high / Thu low (or inverse) play out?
day_deviation_note: # if false, what actually happened?

# Daily Context (leave blank if not relevant)

session_of_entry: # Asian | London | New_York | London_Close
killzone: # specific window e.g. “NY AM 9:30-11:00”
observed_hod_session: # which session actually printed HOD
observed_lod_session: # which session actually printed LOD
session_model_matched: # true | false — did the expected session deliver?
session_deviation_note: # if false, what happened?

# ── What Was the Market Doing Before Entry? ──

htf_trend: # bullish | bearish | ranging | transitioning
price_relative_to_range: # premium | discount | equilibrium
recent_displacement_direction: # up | down | none
open_float: # where is the nearest unmitigated level drawing price?

# ── Entry Details ──

entry_price:
entry_time:
direction: # long | short
stop_loss:
take_profit_1:
take_profit_2:
risk_reward:

# ══════════════════════════════════════════════

# KEY LEVEL — the structural reason for the trade

# ══════════════════════════════════════════════

level_price:
level_type: # order_block | fvg | breaker | mitigation_block | equal_highs_lows | session_hl | weekly_open | monthly_open | liquidity_void
level_timeframe: # M15 | H1 | H4 | D1 | W1 | MN
level_touch_count: # how many times price tested before your entry
level_freshness: # first_touch | second_touch | degraded
level_mitigated: # true | false — was this already partially filled before your entry

# ── Level Hierarchy ──

htf_draw_on_liquidity: # the REAL target — the magnet price hasn’t reached yet
htf_draw_level_type: # equal_highs | equal_lows | untested_ob | liquidity_void | prev_swing
htf_draw_mitigated: # true | false
intermediate_levels: # friction levels between entry and draw (not reversal — just speed bumps)
nearest_opposing_level: # where your thesis structurally dies

# ══════════════════════════════════════════════

# INVALIDATION & WRONGNESS RECOGNITION

# ══════════════════════════════════════════════

invalidation_price: # hard line — thesis is dead here
invalidation_type: # close_through | wick_through | body_close — what counts as invalidation
invalidation_timeframe: # which TF close matters — M15 | H1 | H4 | D1

# Early Warning Signals (BEFORE stop is hit)

early_warning_defined: # what would tell you the trade is weakening BEFORE invalidation

# Examples: “price spends 3+ candles in my OB without displacement”

# “opposing session high/low gets taken without continuation”

# “FVG above my entry gets filled — buyers aren’t holding”

early_warning_triggered: # true | false | na
early_warning_time: # when did the warning fire
early_warning_action: # what did you do — held | reduced | closed | moved_sl | nothing

# ── Bias Was Wrong ──

was_bias_correct: # true | false
when_bias_proved_wrong: # specific candle/time when it became clear
what_signaled_wrong: # what price action showed you — e.g. “displacement through my level with no wick respect”
how_fast_recognized: # immediately | within_1_candle | slow | after_SL_hit | never_during_trade
did_you_act_on_it: # true | false
what_you_did: # closed | flipped | held_and_hoped | reduced | added_to_loser
optimal_action: # what SHOULD you have done in hindsight

# ══════════════════════════════════════════════

# OUTCOME

# ══════════════════════════════════════════════

result: # win | loss | breakeven | partial
pips_gained:
pips_risked:
actual_rr:
exit_price:
exit_time:
exit_reason: # tp_hit | sl_hit | manual_close | early_warning_exit | trailed | bias_flip

# ── Setup Quality ──

setups_this_candle: # total quality setups this candle offered
setup_number: # which one you took (1st, 2nd)
confluence_count: # how many factors aligned
displacement_present: # true | false
market_structure_shift: # true | false
liquidity_swept_before_entry: # true | false

# ══════════════════════════════════════════════

# PATTERN TRACKING — breaking loops, building edges

# ══════════════════════════════════════════════

# Mistake Classification (if loss or suboptimal outcome)

mistake_type: # none | wrong_level | wrong_bias | early_entry | late_entry | ignored_warning | moved_stop | overtraded | revenge_trade | forced_model | no_mistake_just_loss
mistake_repeating: # true | false — have you made this SAME mistake before?
linked_mistake_entries: # [[backtest IDs]] of previous entries with the same mistake
what_broke_the_rule: # emotional trigger — fear_of_missing | anger | overconfidence | boredom | revenge | fatigue | none

# Positive Reinforcement (ALWAYS fill — even on losses)

what_i_did_right: # e.g. “waited for displacement”, “respected the level hierarchy”, “cut early when warning fired”
skill_demonstrated: # patience | level_selection | bias_recognition | risk_management | session_timing | early_exit | none
edge_reinforced: # which part of your system worked even if the trade lost — e.g. “my entry model is solid, the loss was a context read issue”

# ── Tags ──

tags:

- backtest

-----

## Narrative

### Pre-Trade Read

<!-- What was your read BEFORE entering? What was the higher timeframe story? Where was the draw on liquidity? Why did you expect this candle to do what you thought it would do? -->

### What Actually Happened

<!-- What did price ACTUALLY do? Did the candle behave as expected? Where did it deviate? Be forensic — don't just say "it went against me." Describe the price action. -->

### Level Hierarchy — Why This Level, Why Not Another?

<!-- Why was this the right level? Were there levels above/below you ignored? Was there unfinished business (unswept liquidity, unmitigated zones) that should have made you wait? Reference the EUR/USD principle: don't short at the intermediate level when the real supply hasn't been tapped yet. -->

### Touch Behavior Log

<!-- For your key level, what happened at each touch? Did reaction weaken? Did displacement change? This is where you learn whether a level is "degrading." -->

|Touch #|Time/Date|Reaction Type|Displacement?|Held?|Notes|
|-------|---------|-------------|-------------|-----|-----|
|1      |         |             |             |     |     |
|2      |         |             |             |     |     |
|3      |         |             |             |     |     |

### All Setups This Candle Offered

|Setup #|Time|Direction|Level Used|Quality|Result|RR|
|-------|----|---------|----------|-------|------|--|
|1      |    |         |          |       |      |  |
|2      |    |         |          |       |      |  |

### Context Model Deviation

<!-- Did the "standard" model fail here? Week 1 didn't accumulate? Tuesday didn't mark the high? London didn't deliver HOD? DOCUMENT IT. Over time this section tells you WHEN models break and what the actual distribution looks like — not the idealized one. -->

### When I Knew I Was Wrong (or Right)

<!-- Be specific about the MOMENT. What candle? What price action? What time? Did you see it in real time or only in hindsight? If you saw it and didn't act — why? If you acted well — what gave you the confidence to trust the signal? -->

### What I Did Right

<!-- MANDATORY. Even on your worst loss, something went right. Maybe you sized correctly. Maybe you picked the right level but the wrong session. Maybe you cut before full SL. Identify it and own it. This is how you build confidence in your system instead of eroding it. -->

### Mistake Autopsy (if applicable)

<!-- If this was a repeated mistake, link the previous entries. What is the PATTERN? Is this a "I always force the model on Fridays" thing? A "I ignore early warnings during NY session" thing? Name the loop so you can see it across entries. -->

**Mistake pattern name:**
**Previous occurrences:** [[]] [[]]
**What triggers this pattern:**
**What would break the loop:**

### Screenshot

![[]]

-----

## Dataview Dashboard Queries

```
// ── COPY THESE TO A SEPARATE DASHBOARD NOTE AND UNCOMMENT ──

// Win rate by timeframe
// ```dataview
// TABLE
//   length(filter(rows, (r) => r.result = "win")) as Wins,
//   length(rows) as Total,
//   round(length(filter(rows, (r) => r.result = "win")) / length(rows) * 100, 1) + "%" as "Win %"
// FROM "Backtests"
// WHERE result
// GROUP BY trading_timeframe
// ```

// Mistake frequency — find your loops
// ```dataview
// TABLE length(rows) as Count,
//   round(length(rows) / length(filter(pages("Backtests"), (p) => p.result)) * 100, 1) + "%" as "% of All Trades"
// FROM "Backtests"
// WHERE mistake_type AND mistake_type != "none" AND mistake_type != "no_mistake_just_loss"
// GROUP BY mistake_type
// SORT length(rows) DESC
// ```

// Repeating mistakes — the critical ones
// ```dataview
// TABLE mistake_type, what_broke_the_rule, date
// FROM "Backtests"
// WHERE mistake_repeating = true
// SORT date DESC
// ```

// Emotional trigger tracking
// ```dataview
// TABLE length(rows) as Count,
//   round(length(filter(rows, (r) => r.result = "loss")) / length(rows) * 100, 1) + "%" as "Loss %"
// FROM "Backtests"
// WHERE what_broke_the_rule AND what_broke_the_rule != "none"
// GROUP BY what_broke_the_rule
// SORT length(rows) DESC
// ```

// Positive reinforcement — what you do well
// ```dataview
// TABLE length(rows) as Count
// FROM "Backtests"
// WHERE skill_demonstrated AND skill_demonstrated != "none"
// GROUP BY skill_demonstrated
// SORT length(rows) DESC
// ```

// Context model accuracy — how often does the "standard" model actually work?
// ```dataview
// TABLE
//   length(filter(rows, (r) => r.phase_matches_model = true)) as "Model Matched",
//   length(filter(rows, (r) => r.phase_matches_model = false)) as "Model Broke",
//   round(length(filter(rows, (r) => r.phase_matches_model = true)) / length(rows) * 100, 1) + "%" as "Match %"
// FROM "Backtests"
// WHERE phase_matches_model
// GROUP BY current_week_number
// ```

// Weekly day model accuracy
// ```dataview
// TABLE
//   length(filter(rows, (r) => r.day_model_matched = true)) as Matched,
//   length(filter(rows, (r) => r.day_model_matched = false)) as Broke,
//   round(length(filter(rows, (r) => r.day_model_matched = true)) / length(rows) * 100, 1) + "%" as "Match %"
// FROM "Backtests"
// WHERE trading_timeframe = "weekly" AND day_model_matched
// GROUP BY pair
// ```

// Early warning system effectiveness
// ```dataview
// TABLE early_warning_action,
//   length(rows) as Count,
//   round(length(filter(rows, (r) => r.result = "loss")) / length(rows) * 100, 1) + "%" as "Loss %"
// FROM "Backtests"
// WHERE early_warning_triggered = true
// GROUP BY early_warning_action
// ```

// Level type performance
// ```dataview
// TABLE length(rows) as Uses,
//   round(length(filter(rows, (r) => r.result = "win")) / length(rows) * 100, 1) + "%" as "Win %",
//   round(average(rows.actual_rr), 2) as "Avg RR"
// FROM "Backtests"
// WHERE result
// GROUP BY level_type
// ```

// Touch count vs outcome
// ```dataview
// TABLE length(rows) as Trades,
//   round(length(filter(rows, (r) => r.result = "win")) / length(rows) * 100, 1) + "%" as "Win %"
// FROM "Backtests"
// GROUP BY level_touch_count
// ```

// Best/worst sessions
// ```dataview
// TABLE length(rows) as Trades,
//   round(length(filter(rows, (r) => r.result = "win")) / length(rows) * 100, 1) + "%" as "Win %",
//   round(average(rows.actual_rr), 2) as "Avg RR"
// FROM "Backtests"
// WHERE killzone
// GROUP BY killzone
// ```

// How fast you recognize wrongness
// ```dataview
// TABLE length(rows) as Count,
//   round(length(filter(rows, (r) => r.result = "loss")) / length(rows) * 100, 1) + "%" as "Loss Rate"
// FROM "Backtests"
// WHERE was_bias_correct = false
// GROUP BY how_fast_recognized
// ```
```