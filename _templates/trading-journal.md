---
tags:
  - trading-journal
  - crt
source: ""
description: ""
date: {{date}}
result: ""
---

# CRT Trade — {{ticker}} | {{date}}

## Timeframe & Context

| Field | Value |
|-------|-------|
| **Candle Being Traded** | *(Monthly / Weekly / Daily)* |
| **Direction** | *(Long / Short)* |
| **Entry Time** | |
| **Exit Time** | |

---

<!-- ═══════════════════════════════════════════════
     CRT CORE: C1 → C2 → C3
     C1 = Range (establishes high and low)
     C2 = Manipulation (reversal candle, sweeps one side)
     C3 = Distribution (fast move, thick body, short wick)
     ═══════════════════════════════════════════════ -->

# CRT Sequence

## C1 — Range

<!-- C1 establishes the playing field. Your only job here is to identify the high and low. -->

| Field | Value |
|-------|-------|
| **C1 High** | |
| **C1 Low** | |
| **C1 Open** | |
| **C1 Close** | |
| **C1 Body Type** | *(Doji / Small body / Indecision)* |
| **Range Size (pips/points)** | |

### C1 Gate — Is the range set?

| # | IF | THEN | ✓ |
|---|-----|------|---|
| 1.1 | C1 has a defined high and low | Range is established → mark levels | ☐ |
| 1.2 | C1 body is relatively small / indecisive compared to prior candles | Compression present → supports CRT | ☐ |
| 1.3 | C1 high or low sits near a HTF key level (PD array, liquidity) | Range is meaningful, not random → proceed | ☐ |

> **If any fail →** Range is unclear. Wait for it to develop.

---

## C2 — Manipulation (Reversal)

<!-- C2 sweeps one side of C1's range to grab liquidity, then reverses.
     This is the trap. Identify WHICH side got swept and WHERE price reversed. -->

| Field | Value |
|-------|-------|
| **Side Swept** | *(C1 High / C1 Low)* |
| **Sweep Price** | |
| **Reversal Price** | |
| **C2 Open** | |
| **C2 Close** | |
| **Did C2 close back inside C1 range?** | *(Y/N)* |

### C2 Gate — Is the manipulation confirmed?

| # | IF | THEN | ✓ |
|---|-----|------|---|
| 2.1 | C2 sweeps beyond C1 high or C1 low (wick through the level) | Liquidity has been taken → proceed | ☐ |
| 2.2 | C2 reverses and closes back inside or near the opposite side of C1 range | Manipulation is confirmed, not a breakout → proceed | ☐ |
| 2.3 | The sweep aligns with taking out resting liquidity (stops above/below) | Smart money narrative present → proceed | ☐ |
| 2.4 | Bearish: C2 swept C1 high → enter above C1 open / Bullish: C2 swept C1 low → enter below C1 open | Entry side is defined → prepare for C3 | ☐ |

> **If 2.1 fails →** No sweep happened. CRT is not active.
> **If 2.2 fails →** This might be a legitimate breakout, not manipulation. Do not fade.

**Entry Logic:**

- IF **bearish CRT** (C2 swept high) → look for **entry above C1 opening price**
- IF **bullish CRT** (C2 swept low) → look for **entry below C1 opening price**

---

## C3 — Distribution (The Move)

<!-- C3 is the payoff. Fast move, thick body, short wicks.
     If you're not in by the time C3 starts displacing, don't chase. -->

| Field | Value |
|-------|-------|
| **C3 Open** | |
| **C3 Close** | |
| **C3 Body Size** | |
| **C3 Wick Ratio** | *(Short wicks / thick body = clean distribution)* |
| **Did C3 reach the opposite side of C1?** | *(Y/N)* |
| **Did C3 exceed C1 range?** | *(Y/N)* |

### C3 Gate — Is distribution clean?

| # | IF | THEN | ✓ |
|---|-----|------|---|
| 3.1 | C3 moves aggressively in the expected direction (thick body) | Distribution is underway → hold or manage | ☐ |
| 3.2 | C3 has short wicks relative to body | Conviction is strong → trust the move | ☐ |
| 3.3 | C3 reaches or exceeds opposite side of C1 range | Full CRT complete → target hit zone | ☐ |

> **If C3 stalls or produces long wicks →** Distribution is weak. Consider early exit or tighter management.

---

# Timeframe Mapping

<!-- Fill in ONLY the section that matches your traded candle.
     This maps the abstract C1/C2/C3 to the specific time divisions. -->

## Monthly CRT

*(Use when trading the monthly candle)*

| CRT Phase | Maps To | Date Range | Notes |
|-----------|---------|------------|-------|
| **C1 (Range)** | Week 1 | | *Month opens, range establishes* |
| **C2 (Manipulation)** | Week 2 | | *Sweep of Week 1 high or low* |
| **C3 (Distribution)** | Week 3–4 | | *Expansion toward monthly target* |

| Field | Value |
|-------|-------|
| **Monthly Open Price** | |
| **Week 1 High** | |
| **Week 1 Low** | |
| **Which side did Week 2 sweep?** | *(W1 High / W1 Low)* |
| **Week 2 reversal confirmed by?** | |
| **Week 3–4 target** | |

---

## Weekly CRT

*(Use when trading the weekly candle. Select the ICT weekly profile that matches.)*

**Weekly Profile:** *(check one)*

- ☐ **Classic Tuesday Reversal** — Mon = C1, Tue = C2 (sweep + reverse), Wed–Thu = C3
- ☐ **Wednesday Reversal** — Mon–Tue = C1 (trend/range), Wed = C2 (reversal), Thu–Fri = C3
- ☐ **Monday Reversal** — Fri (prior) = C1, Mon = C2 (gap/sweep + reverse), Tue–Wed = C3
- ☐ **Thursday Reversal** — Mon–Wed = C1 (extended range), Thu = C2, Fri = C3
- ☐ **Consolidation / No Clean CRT** — range-bound week, no clear C2 sweep

| CRT Phase | Day(s) | OHLC | Notes |
|-----------|--------|------|-------|
| **C1 (Range)** | | | |
| **C2 (Manipulation)** | | | |
| **C3 (Distribution)** | | | |

| Field | Value |
|-------|-------|
| **Weekly Open Price** | |
| **C1 Day(s) High** | |
| **C1 Day(s) Low** | |
| **Which side did C2 day sweep?** | *(C1 High / C1 Low)* |
| **C2 reversal confirmed by?** | |
| **C3 target** | |
| **Did Friday close confirm distribution?** | *(Y/N)* |

---

## Daily CRT

*(Use when trading the daily candle)*

| CRT Phase | Maps To | Time Range | Notes |
|-----------|---------|------------|-------|
| **C1 (Range)** | Asian Session | 18:00–00:00 EST | *Overnight range sets the high/low* |
| **C2 (Manipulation)** | London / London-NY Overlap | 02:00–10:00 EST | *Sweep of Asian high or low* |
| **C3 (Distribution)** | NY AM / NY PM | 10:00–16:00 EST | *Expansion / real move of the day* |

| Field | Value |
|-------|-------|
| **Daily Open Price (17:00 EST)** | |
| **Asian High** | |
| **Asian Low** | |
| **Asian Range Size** | |
| **Which side did London sweep?** | *(Asian High / Asian Low)* |
| **Sweep time** | |
| **Reversal confirmed at** | |
| **NY target** | |

### Daily Session Detail

| Session | Open | High | Low | Close | Notes |
|---------|------|------|-----|-------|-------|
| **Asian** | | | | | |
| **London** | | | | | |
| **NY AM** | | | | | |
| **NY PM** | | | | | |

---

# Execution

## Entry

| Field | Value |
|-------|-------|
| **CRT Phase at Entry** | *(Entering during C2 reversal / Early C3)* |
| **Entry Price** | |
| **Entry Relative to C1 Open** | *(Above / Below — must match CRT rule)* |
| **Stop Loss** | *(Behind C2 sweep / C1 extreme)* |
| **Take Profit** | *(Opposite side of C1 / Extension beyond)* |
| **Risk (R)** | |
| **Position Size** | |
| **Risk-Reward Ratio** | |

### Entry Gate — Final check before clicking

| # | IF | THEN | ✓ |
|---|-----|------|---|
| E.1 | All C1 + C2 gates passed | CRT is active → proceed | ☐ |
| E.2 | Bearish: price is above C1 open / Bullish: price is below C1 open | Entry is on the correct side → proceed | ☐ |
| E.3 | Stop loss is behind a logical level (C2 wick / C1 extreme) | Risk is defined → proceed | ☐ |
| E.4 | Target is at minimum the opposite side of C1 range | R:R is acceptable → ENTER | ☐ |

> **If any fail →** Do not enter. Log what was missing below:

---

## Management

| # | IF | THEN | ✓ |
|---|-----|------|---|
| M.1 | Price moves to 1R in my favor | Move stop to break-even | ☐ |
| M.2 | Price reaches midpoint of C1 range (50%) | Consider first partial: ___ % | ☐ |
| M.3 | Price reaches opposite side of C1 range | Take profit or trail stop tight | ☐ |
| M.4 | C3 candle starts showing long wicks / stalling | Distribution is weakening → tighten or exit | ☐ |
| M.5 | Price reverses back through C1 open against me | CRT thesis is failing → exit | ☐ |

**Notes during trade:**

---

## Result

| Field | Value |
|-------|-------|
| **Outcome** | *(Win / Loss / BE)* |
| **Exit Price** | |
| **Exit Type** | *(TP / SL / BE / Manual / Rule Break)* |
| **P&L (R)** | |
| **P&L ($)** | |
| **Partial(s) Taken?** | |

---

# Key Levels

| Level | Price | Timeframe | Type |
|-------|-------|-----------|------|
| | | | *(OB / FVG / Breaker / BSL / SSL / EQ / Session HL / Other)* |
| | | | |
| | | | |

---

# Orderflow & Liquidity

- **Buy-side liquidity resting at:**
- **Sell-side liquidity resting at:**
- **Which side did C2 target?**
- **Displacement after sweep?** *(Y/N — describe)*

---

# Pre-Trade Thesis

> **Given** [HTF context — where is price in the bigger CRT?]
>
> **C1 established** [range high/low at ___]
>
> **C2 swept** [which side, at what price]
>
> **So I expect C3 to** [move where, why]
>
> **I'm wrong if** [what breaks this — price reclaims C2 sweep, C3 fails to displace, etc.]

---

# Post-Trade Review

### Was the CRT read correct?
<!-- Did C1/C2/C3 play out as mapped? -->


### What phase was misread (if any)?
<!-- Was C2 actually a breakout? Was C1 range too wide? Did C3 fail to distribute? -->


### Discipline Check

| Question | Answer |
|----------|--------|
| **Did I wait for C2 confirmation before entering?** | *(Y/N)* |
| **Did I enter on the correct side of C1 open?** | *(Y/N)* |
| **Did I follow management rules?** | *(Y/N)* |
| **Protocol loss or discipline loss?** | *(Protocol = rules followed, market didn't cooperate / Discipline = broke rules)* |
| **Gate that needs refinement** | |
| **Proposed rule update** | *(Review after 10+ trades before adopting)* |

---

# Backtesting Tags

| Field | Value |
|-------|-------|
| **Candle Traded** | *(Monthly / Weekly / Daily)* |
| **Weekly Profile (if weekly)** | *(Classic Tue / Wed Rev / Mon Rev / Thu Rev / Consol)* |
| **Session (if daily)** | *(Asian / London / NY)* |
| **C2 Swept** | *(High / Low)* |
| **Entry Side Correct** | *(Y/N)* |
| **C3 Reached Opposite C1** | *(Y/N)* |
| **C3 Exceeded C1 Range** | *(Y/N)* |
| **Day of Week** | |
| **Confluence Score (1-5)** | |
| **Emotional State** | *(Calm / FOMO / Revenge / Confident / Hesitant)* |
| **Protocol Followed** | *(Y/N)* |
| **Loss Type** | *(Protocol / Discipline / N/A)* |
| **Grade (A+ to F)** | |

---

# Screenshots

- **C1 Range:**
- **C2 Manipulation / Sweep:**
- **C3 Distribution:**
- **Entry:**
- **Result:**

---

# Lessons & Connections

- **Key Takeaway:**
- **Pattern Observed:**
- **Related Trades:** [[]]
