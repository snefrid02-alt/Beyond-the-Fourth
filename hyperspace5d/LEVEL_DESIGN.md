/*
 * This is free and unencumbered software released into the public domain.
 * For more information, please refer to <http://unlicense.org/>
 */

# HyperSpace5D - Level Design Documentation

## Overview

This document explains the design philosophy, intended solutions, and teaching objectives for each level in HyperSpace5D. The game features 11 levels that progressively teach players to think in five dimensions.

---

## Level Progression Philosophy

### Early Game (Levels 1-3): Foundation
- **Focus**: Basic mechanics and single-concept puzzles
- **Goal**: Make 5D space comprehensible
- **Difficulty**: ⭐☆☆

### Mid Game (Levels 4-7): Combination
- **Focus**: Combining multiple mechanics, intermediate complexity
- **Goal**: Build confidence with dimensional thinking
- **Difficulty**: ⭐⭐☆

### Late Game (Levels 8-10): Mastery
- **Focus**: Complex multi-mechanic puzzles requiring all skills
- **Goal**: Prepare for final challenge
- **Difficulty**: ⭐⭐⭐

### Boss (Level 11): Ultimate Challenge
- **Focus**: All mechanics under pressure
- **Goal**: Test complete mastery of 5D navigation
- **Difficulty**: ⭐⭐⭐⭐⭐

---

## Level 1: Introduction to 5D Space

### Teaching Objectives
- Understand dimensional rotation controls (Q/E/R keys)
- Learn that objects exist in all 5 dimensions simultaneously
- Grasp the concept of "hidden" dimensions
- Realize objects can be invisible in one view but visible in another

### Level Layout
```
Start (XYZ: 0,2,0,0,0) → Hidden Platform (XYZ: 8,1,0,5,0) → Wall → Goal (XYZ: 15,3,0,0,0)
```

### Intended Solution Path

1. **Start in XYZ view** (default)
   - See starting platform and goal in distance
   - Notice wall blocking direct path

2. **Observe the gap**
   - Platform at (8,1,0,0,0) is not visible or is barely visible (far in hidden dimensions)
   - Cannot reach goal directly

3. **Press Q to rotate to XYW view**
   - Hidden platform at W=5 becomes clearly visible
   - Platform is now solid and reachable

4. **Jump to hidden platform**
   - Land on platform in XYW view
   - Platform exists at same XY position but different W coordinate

5. **Continue in XYW or switch back**
   - Wall at (6,3,0,0,0) only blocks in XYZ view
   - Can bypass by staying in W-dimension or jumping over

6. **Reach goal**
   - Goal is accessible from multiple views
   - Success!

### Skills Learned
- ✓ Basic dimensional rotation
- ✓ Objects exist in all dimensions
- ✓ Different views reveal different geometry
- ✓ Trust what you can't see (yet)

### Common Mistakes & Hints
- **Mistake**: Trying to jump the gap in XYZ view
  - **Hint**: "That platform looks far away... maybe it's close in another dimension?"

- **Mistake**: Not realizing Q/E rotate dimensions
  - **Hint**: "Try pressing Q or E to see space from a different angle"

---

## Level 2: 5D Platforming (Moving Platforms)

### Teaching Objectives
- Timing jumps with moving platforms
- Understanding platforms moving through hidden dimensions
- Objects appearing/disappearing as they move through dimensional space
- Predicting platform positions across views

### Level Layout
```
Start → Moving Platform 1 (X-Y motion) → Moving Platform 2 (W motion) → 
Static Mid → Moving Platform 3 (V motion) → Goal
```

### Intended Solution Path

1. **Platform 1: Standard 3D movement**
   - Moves in X-Y plane (visible in XYZ view)
   - Time jump as it rises
   - **Skill**: Basic timing

2. **Platform 2: W-dimension movement**
   - Moves from W=-3 to W=+3
   - Appears to fade in/out in XYZ view as it moves through W
   - **Solution**: Switch to XYW view to see full movement
   - Jump when platform is at W=0 (intersects XYZ space)
   - **Skill**: Timing with dimensional visibility

3. **Platform 3: V-dimension movement**
   - Moves from V=-4 to V=+4
   - Only consistently visible in XYV or ZWV views
   - **Solution**: Switch to XYV view, time jump
   - **Skill**: Multi-dimensional awareness

4. **Reach goal**
   - Final platform visible in all views

### Skills Learned
- ✓ Timing platforming challenges
- ✓ Tracking objects moving through hidden dimensions
- ✓ Predicting when objects intersect current view
- ✓ Quick dimensional switching

### Advanced Strategy
- Expert players can dash between platforms for speed
- Can stay in one view and predict intersections (harder)

---

## Level 3: Hypercube Maze

### Teaching Objectives
- Complex 5D topology
- Strategic dimension rotation planning
- Understanding how walls exist in some views but not others
- Multi-step puzzle requiring multiple view changes

### Level Layout
```
Maze with walls at:
- W=0, V=0 (blocks XYZ, XYW, XYV views)
- Z=0, V=0 (blocks XYW view)
- Z=0, W=0 (blocks XYV view)

Path requires navigating through all three dimensional configurations.
```

### Intended Solution Path

1. **Start in XYZ view**
   - Wall 1 blocks forward progress
   - Platform visible to the right at (8,1,5,0,0)

2. **Move to side platform**
   - Requires jumping/moving in Z dimension
   - **Hint**: Use WASD to navigate the visible 3D slice

3. **Switch to XYW view (Press Q)**
   - Wall 2 now blocks, but Wall 1 is passable
   - See platform at (12,1,0,5,0) in W dimension
   - Navigate toward it

4. **Switch to XYV view (Press E)**
   - Wall 3 becomes obstacle, others passable
   - Platform at (18,1,0,0,5) visible
   - Path through V dimension opens

5. **Strategic switching**
   - May need to switch between views multiple times
   - Some platforms only accessible from certain angles
   - Complex structure at (22,3,3,3,3) requires viewing from multiple perspectives

6. **Reach goal**
   - Goal at (30,3,0,0,0) accessible after navigating maze

### Skills Learned
- ✓ Strategic dimension rotation
- ✓ Mental mapping of 5D space
- ✓ Planning multi-step dimensional paths
- ✓ Understanding dimensional occlusion

### Design Notes
- Multiple valid solution paths
- Encourages exploration
- Rewards players who experiment with all views

---

## Level 4: Pentacube Maze

### Teaching Objectives
- Comprehensive dimensional rotation mastery
- Understanding hypercube structure
- Using all 10 dimensional views
- Complex 5D spatial reasoning

### Level Layout
```
5D hypercube maze with sections visible in different view combinations:
- XYZ sections (standard paths)
- W-dimension passages (XYW, XZW, YZW views)
- V-dimension passages (XYV, XZV, YZV views)
- WV-dimension passages (XWV, YWV, ZWV views)
```

### Intended Solution Path

1. **Explore XYZ sections**
   - Central cube core and connected paths
   - Get familiar with basic structure

2. **Discover W-dimension passages**
   - Switch to XYW view (key 2)
   - See green-tinted passages
   - Navigate through W-space (around position W=5-8)

3. **Use V-dimension shortcuts**
   - Switch to XYV view (key 3)
   - Blue-tinted passages visible
   - Jump to platforms at V=6

4. **Navigate WV-combined spaces**
   - Switch to XWV or YWV views (keys 8-9)
   - Purple platforms at (35, 2, 0, 4, 4)
   - Requires understanding 4D hypersurface

5. **Stepping stones through dimensions**
   - Platforms at different 5D coordinates
   - Must switch views mid-jump (advanced)
   - Sequence: (17,3,2) → (22,3,0,3,0) → (27,3,0,0,4) → (32,3,0,2,2)

6. **Reach hypercube corner**
   - Goal at (40,3,0,0,0)

### Skills Learned
- ✓ All 10 dimensional views
- ✓ Hypercube topology
- ✓ Complex 5D path planning
- ✓ Quick view switching

### Pro Tips
- Map out structure in your mind
- Use color coding to remember dimensions
- W-dimension = green, V-dimension = blue, WV = purple

---

## Level 5: Dimensional Bridges

### Teaching Objectives
- Mid-air dimension switching
- Trusting invisible platforms
- Reaction timing
- Mental model of multi-view space

### Level Layout
```
Series of bridges, each existing in only 1-2 dimensional views:
Bridge 1: Visible in XYZ, invisible in XYW
Bridge 2: Visible in XYW, invisible in XYZ
Bridge 3: Visible in XYV only
Bridge 4: Visible in YZW only (perpendicular to X)
```

### Intended Solution Path

1. **Bridge 1 (red)**
   - Start in XYZ view (key 1)
   - Bridge is solid and visible
   - Cross normally

2. **Switch to XYW mid-crossing**
   - As you cross Bridge 1, prepare for Bridge 2
   - At safety platform, switch to XYW view (key 2)
   - Bridge 2 (green) appears, Bridge 1 fades

3. **Bridge 2 crossing**
   - Cross Bridge 2 in XYW view
   - **Advanced**: Switch views mid-jump to see both bridges briefly

4. **Bridge 3 (blue) - Trust exercise**
   - Switch to XYV view (key 3)
   - Bridge 3 appears thin (only substantial in V dimension)
   - Take leap of faith across thin-looking bridge

5. **Bridge 4 (yellow) - Perpendicular jump**
   - Switch to YZW view (key 6)
   - Bridge is perpendicular to usual movement axis
   - Different navigation required

6. **Reach goal**
   - Multiple paths possible
   - Safety platforms provide checkpoints

### Skills Learned
- ✓ Mid-air view switching
- ✓ Trust in geometry
- ✓ Reaction speed
- ✓ Spatial confidence

### Challenge Variants
- **Speedrun**: Cross all bridges without touching safety platforms
- **Minimalist**: Use fewest view changes possible

---

## Level 6: Hyperspace Teleportation

### Teaching Objectives
- Non-Euclidean spatial relationships
- 5D topology and adjacency
- Portal mechanics in higher dimensions
- Understanding space can "fold"

### Level Layout
```
Portal pairs connecting distant 5D points:
Portal 1: (10,2,0,0,0) ↔ (15,2,0,15,0)  [far in W]
Portal 2: (20,2,0,15,0) ↔ (25,2,0,0,20) [far in V]
Portal 3: (30,2,0,0,20) ↔ (45,2,0,0,0)  [near goal]
```

### Intended Solution Path

1. **Red Portal Pair**
   - Step on red platform at (10,2,0,0,0)
   - In full implementation, this would teleport to (15,2,0,15,0)
   - **Teaching**: What's far can be near

2. **Navigate to Blue Portal Entry**
   - From W=15 position, move to (20,2,0,15,0)
   - Requires XYW view to see path clearly
   - Connecting platforms at intermediate W values

3. **Blue Portal to V-space**
   - Teleport to (25,2,0,0,20) - far in V dimension
   - Dramatic perspective shift
   - **Teaching**: 5D allows non-local connections

4. **Green Portal Home**
   - At V=20, find green portal at (30,2,0,0,20)
   - Teleports near goal at (45,2,0,0,0)
   - **Teaching**: Completing 5D circuit

5. **Reach goal**
   - Short distance from final portal exit

### Skills Learned
- ✓ 5D spatial topology
- ✓ Non-local thinking
- ✓ Trust in higher-dimensional geometry
- ✓ Mental remapping of space

### Design Philosophy
- Portals represented visually by color-coded semi-transparent platforms
- In full implementation, stepping on portal would smoothly transition
- Teaches that 5D space has different connectivity than 3D

---

## Level 7: Phase Objects

### Teaching Objectives
- Dimensional occupancy concept
- Hypervolume intersection
- Selective interaction based on view
- Understanding "thickness" in dimensions

### Level Layout
```
Phase platforms (thin in different dimensions):
- XY-phase: Thick in X,Y; thin in Z,W,V
- XW-phase: Thick in X,W; thin in Y,Z,V
- XV-phase: Thick in X,V; thin in Y,Z,W
- YZ-phase: Thick in Y,Z; thin in X,W,V
- WV-phase: Thick in W,V; thin in X,Y,Z
```

### Intended Solution Path

1. **XY-Phase Platform (red)**
   - Start in XYZ view
   - Platform looks normal, is solid
   - **Teaching**: Some objects are thick in visible dimensions

2. **XW-Phase Platform (green)**
   - Switch to XYW view (key 2)
   - Platform that was thin now appears substantial
   - Only solid when W is visible dimension
   - **Teaching**: Dimensional thickness matters for interaction

3. **XV-Phase Platform (blue)**
   - Switch to XYV view (key 3)
   - Platform substantial in this view
   - Jump requires being in correct dimensional view

4. **YZ-Phase Platform (yellow)**
   - Switch to YZW or YZV view (keys 6-7)
   - Platform perpendicular to usual motion
   - **Advanced**: Navigate when Y and Z are both visible

5. **WV-Phase Platform (purple)**
   - Switch to XWV, YWV, or ZWV view (keys 8-10)
   - Only solid when both W and V are visible
   - **Teaching**: Some objects only exist in higher-dimensional slices

6. **Transitional platforms**
   - Gray platforms solid in all views
   - Provide safe checkpoints

7. **Reach goal**

### Skills Learned
- ✓ Understanding dimensional occupancy
- ✓ Hypervolume concepts
- ✓ Selective phasing
- ✓ Advanced 5D geometry

### Technical Detail
Platforms have size (6, 2, 0.5, 0.5, 0.5) type format:
- Large size in two dimensions = solid platform in those dimensions
- Small size (0.5) = thin/intangible in that dimension
- Collision only occurs when all player dimensions intersect solid parts

---

## Level 8: 5D Rotation Puzzles

### Teaching Objectives
- Sequential dimensional rotation
- Combination lock concept
- Precise dimensional control
- Memory and pattern recognition

### Level Layout
```
Three puzzle locks:
Lock 1: Key visible in XYW (requires switch from XYZ)
Lock 2: Keys in XYV then XWV (two-step sequence)
Lock 3: Keys in XYW, XYV, XWV (three-step combination)
```

### Intended Solution Path

1. **Puzzle 1: Single Rotation**
   - Lock (red wall) blocks path in XYZ view
   - Switch to XYW view (key 2)
   - Key platform (gold) visible at W=5
   - Jump to key, conceptually "unlocks" Lock 1
   - **Teaching**: Single dimensional shift solves puzzle

2. **Puzzle 2: Two-Step Sequence**
   - Lock blocks in XYZ
   - Must visit two key platforms in order:
     a. Switch to XYV view (key 3), reach key at V=6
     b. Switch to XWV view (key 8), reach key at (W=6, V=6)
   - **Teaching**: Sequential dimensional navigation

3. **Puzzle 3: Three-Way Combination**
   - Complex lock with three barriers
   - Must collect three keys in specific order:
     a. XYW view → key at W=7
     b. XYV view → key at V=7
     c. XWV view → key at (W=7, V=7)
   - **Teaching**: Complex sequential puzzles
   - **Challenge**: Remember sequence, execute precisely

4. **Lock opens**
   - After collecting all keys in sequence
   - Path to goal clears

5. **Reach goal**

### Skills Learned
- ✓ Sequential dimensional thinking
- ✓ Pattern memorization
- ✓ Precise view control
- ✓ Puzzle-solving in 5D

### Design Notes
- Keys are color-coded gold
- Locks are red obstacles
- Could be extended with even more complex combinations
- Teaches patient, methodical dimensional exploration

---

## Level 9: Temporal Echoes

### Teaching Objectives
- V-dimension as pseudo-temporal
- Creative platform generation
- Self-assistance concept
- Trail planning

### Level Layout
```
V-dimension treated as a time-like dimension:
- Echo generators create platforms at different V coordinates
- Platforms at V=-15 to V=+15 in steps
- V-dimension staircase from V=0 to V=27
```

### Intended Solution Path

1. **Discover Echo Mechanism**
   - Step on blue echo generator at (10,2,0,0,0)
   - Generator spans V=-7.5 to V=+7.5
   - Creates platforms at multiple V coordinates
   - **Teaching**: Movement through V leaves "trail"

2. **Use Echoes as Platforms**
   - Switch to XYV view (key 3)
   - See echo platforms at (15, 2, 0, 0, -15) to (15, 2, 0, 0, +15)
   - Jump between echoes
   - **Teaching**: Past positions in V can be used as platforms

3. **Second Echo Section**
   - Larger echo generator at (25,2,0,0,0)
   - Spans V=-10 to V=+10
   - More echo platforms generated
   - **Teaching**: Larger generators = more echoes

4. **V-Dimension Staircase**
   - Platforms at increasing V coordinates
   - (45, 2, 0, 0, 0) → (47, 2.5, 0, 0, 3) → (49, 3, 0, 0, 6) → ...
   - Each step at +0.5Y and +3V
   - **Teaching**: Climbing through V dimension

5. **Reach Goal at High V**
   - Goal at (70, 9, 0, 0, 27)
   - High up in both Y and V dimensions
   - **Teaching**: V can be treated like height

### Skills Learned
- ✓ Creative use of 5th dimension
- ✓ Trail-based platforming
- ✓ Pseudo-temporal thinking
- ✓ 5D height concepts

### Philosophical Note
- V-dimension isn't actually time, but this level lets players imagine it that way
- Creates intuition bridge between spatial 5D and 4D + time
- "Echoes" are just platforms at different V coordinates, but feel like time trail

---

## Level 10: Hypersurface Walking

### Teaching Objectives
- 4D hypersurface intuition
- Embedding in 5D space
- Advanced topology
- Connected structure across views

### Level Layout
```
4D "cylinder" (3-sphere) embedded in 5D:
- 24 segments around parametric curve
- Each segment has 20 steps along length
- Appears as different shapes in different views
- All connected in 4D structure
```

### Intended Solution Path

1. **Recognize Hypersurface**
   - Colored platforms in curved pattern
   - Colors shift from red → green → blue → purple → red
   - **Teaching**: This is one connected 4D structure

2. **Start Walking**
   - Begin on nearest segment
   - Platform colors guide direction
   - Follow color gradient

3. **Switch Views to See Path**
   - XYZ view: Appears as helical curve
   - XYW view: Different helical pattern
   - XYV view: Another perspective
   - **Teaching**: Same structure, different appearances

4. **Navigate the Twist**
   - Parametric equations create twist:
     - Y = 2 + 10×cos(θ)
     - Z = 10×sin(θ)
     - W = 10×cos(θ + t×π)
     - V = 10×sin(θ + t×π)
   - Surface twists through 4D as you walk
   - **Teaching**: 4D structures can twist in ways impossible in 3D

5. **Follow to End**
   - Guide platforms (yellow) mark waypoints
   - All segments connect to form closed 4D loop
   - Goal at end of parametric path

6. **Reach goal**
   - At (45, 3, 0, 0, 0)

### Skills Learned
- ✓ 4D hypersurface intuition
- ✓ Understanding embedding
- ✓ Parametric geometry
- ✓ Advanced 5D topology

### Mathematical Beauty
- This level showcases elegant math
- Hypersurface is a torus-like structure in 5D
- Appears completely different from each viewing angle
- All perspectives show same connected path

---

## Level 11: The Pentarch (Boss Fight)

### Teaching Objectives
- Apply ALL previous skills under pressure
- Quick dimensional switching in combat
- Strategic planning in dynamic environment
- Master-level 5D navigation

### Boss Mechanics

#### The Pentarch: 5D Entity
- **5 Cores**, each vulnerable from one specific view:
  1. **Red Core**: XYZ view (0,1,2)
  2. **Green Core**: XYW view (0,1,3)
  3. **Blue Core**: XYV view (0,1,4)
  4. **Yellow Core**: XZW view (0,2,3)
  5. **Purple Core**: YZW view (1,2,3)

#### Boss Phases
1. **Phase 1 (5 cores active)**
   - Slow projectile attacks
   - Stable arena
   - 3-second attack interval

2. **Phase 2 (3-4 cores active)**
   - Faster projectiles
   - Some geometry changes
   - 2.5-second attack interval

3. **Phase 3 (2 cores active)**
   - Fast projectiles
   - Dynamic platform movement
   - 2-second attack interval
   - Occasional hyperwalls

4. **Phase 4 (1 core active)**
   - Extremely fast attacks
   - Chaotic geometry
   - 1.5-second attack interval
   - Frequent hyperwalls
   - Platform directions reverse randomly

#### Boss Attacks

**Projectile Barrage**
- Fired from each active core
- Travel through 5D space
- Appear/disappear in different views
- Speed increases with phase

**5D Hyperwalls**
- 4D walls blocking movement
- Thin in one dimension
- Appear randomly in phases 3-4
- Must dodge or rotate dimensions to pass

**Dimensional Forcing**
- Could force player view changes (advanced)
- Disorient spatial sense

**Geometry Manipulation**
- Moving platforms speed up
- Platforms change directions
- Safe zones shrink

### Intended Strategy

#### Core 1 (Red - XYZ View)
1. **Initial Phase**
   - Stay in standard XYZ view
   - Learn attack patterns
   - Identify core location (20, 8, 0, 0, 0)

2. **Attack Window**
   - Between projectile volleys
   - Dash or jump toward core
   - Need to reach attack range

3. **Damage Core**
   - In full implementation, would have attack button
   - Reduce core health to zero
   - Core destroys, turns transparent

#### Core 2 (Green - XYW View)
1. **Switch Perspective**
   - Press key 2 for XYW view
   - Core at (20, 8, 0, 15, 0) becomes solid
   - Was far in W dimension

2. **Navigate W-space**
   - Use moving platforms
   - Avoid projectiles (harder to track in different view)

3. **Attack Core**
   - Boss now in Phase 2 (more aggressive)

#### Core 3 (Blue - XYV View)
1. **Switch to XYV**
   - Press key 3
   - Core at (20, 8, 0, 0, 15) accessible

2. **Navigate V-space**
   - Use high V-coordinate platforms
   - Boss attacks faster now

3. **Destroy Core**
   - Entering Phase 3 (chaotic)

#### Core 4 (Yellow - XZW View)
1. **Advanced View**
   - Press key 4 for XZW
   - Core at (20, 8, 12, 8, 0)
   - Requires simultaneous Z and W navigation

2. **Combat in XZW Space**
   - Hyperwalls begin appearing
   - Platform movements erratic
   - Must time movements carefully

3. **Eliminate Core**
   - Phase 4 begins (one core left)

#### Core 5 (Purple - YZW View)
1. **Final Challenge**
   - Press key 6 for YZW view
   - Core at (20, 12, 8, 8, 0)
   - Most difficult perspective (no X axis visible)

2. **Extreme Combat**
   - Maximum aggression
   - Hyperwalls everywhere
   - Platforms chaotic
   - 1.5-second attack interval

3. **Victory**
   - Destroy final core
   - All attacks cease
   - Goal platform appears at (40, 3, 0, 0, 0)

### Skills Required
- ✓ All 10 dimensional views
- ✓ Quick view switching
- ✓ Combat spatial awareness
- ✓ Projectile dodging in 5D
- ✓ Dynamic platform navigation
- ✓ Strategic planning
- ✓ Adaptation to changing geometry
- ✓ Master-level 5D thinking

### Victory Rewards
- **Achievement**: "Pentarch Defeated"
- **Stats Display**:
  - Total time
  - Dimensional rotations used
  - Hits taken
  - Perfect clear bonus (no hits)

### Design Philosophy
- Boss fight tests ALL skills learned
- Each core requires different dimensional mastery
- Escalating difficulty mirrors player skill growth
- Dynamic arena prevents pattern memorization
- Victory is achievable but challenging
- Rewards aggressive dimensional switching

---

## General Design Principles

### Progressive Difficulty
1. **Single Concept** (Levels 1-3)
2. **Concept Combination** (Levels 4-7)
3. **Mastery Required** (Levels 8-10)
4. **Ultimate Test** (Level 11)

### Visual Feedback
- **Color Coding**:
  - Red/Orange = W dimension
  - Blue/Cyan = V dimension
  - Purple/Magenta = W+V combined
  - Yellow = Multiple dimensions
  - Green = Safe zones

- **Opacity**:
  - Far in hidden dimensions = more transparent
  - Close in hidden dimensions = more opaque

- **Scale**:
  - Far in hidden dimensions = appears smaller
  - Close in hidden dimensions = appears larger

### Player Guidance
- **Subtle Hints**:
  - Platform colors suggest which view to use
  - Visual trails show dimensional paths
  - Goal always visible (glowing green)

- **No Hand-Holding**:
  - Players encouraged to explore
  - Multiple solution paths when possible
  - Discovery is rewarding

### Accessibility Options (Future)
- Slow-motion mode for timing challenges
- Extended attack windows for combat
- Visual guides for dimensional relationships
- Practice mode for specific mechanics

---

## Speedrun Potential

### Level-Specific Skips
- **Level 2**: Dash between moving platforms
- **Level 4**: Direct path through WV space
- **Level 5**: Bridge skip with dash timing
- **Level 8**: Minimum view changes

### Boss Rush Mode (Future)
- Fight all cores consecutively
- Time attack challenge
- Leaderboard integration

---

## Educational Value

These levels teach:
1. **Spatial Reasoning**: Thinking beyond 3D
2. **Abstract Mathematics**: Linear algebra, topology
3. **Problem Solving**: Multi-step puzzle planning
4. **Adaptability**: Dynamic challenge response
5. **Confidence**: Mastering difficult concepts

Players who complete all 11 levels have genuinely learned to think in five dimensions - a rare and valuable cognitive skill!

---

**End of Level Design Documentation**

*This document is a living design guide. As the game evolves, level designs may be refined based on player feedback and testing.*
