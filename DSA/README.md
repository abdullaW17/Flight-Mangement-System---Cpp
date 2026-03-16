# ✈️ Flight Management System

A **C++ console and graphical application** for managing and querying international flight routes. Built as a Data Structures & Algorithms (DSA) project, it models the global flight network as a **directed weighted graph** using custom adjacency lists, and provides both terminal and SFML-powered visual output modes.

---

## 👥 Team Members

| Roll Number  |
|--------------|
| 23I-2096     |
| 23I-2069     |
| 23I-2064     |

---

## 📋 Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **View All Flights** | List every flight in the system (terminal or graphical view) |
| 2 | **Search Flights** | Find flights between two cities on a specific date |
| 3 | **Book Flight** | Book a seat on a chosen flight route |
| 4 | **Shortest Route** | Find the cheapest/shortest path between two cities using graph traversal |
| 5 | **Flights with Preferences** | Filter results by preferred airline and layover city |
| 6 | **Flights with Layovers** | Discover multi-hop routes with intermediate stops |
| 7 | **Advanced Route Generation** | Generate all possible routes between a source and destination |
| 8 | **Subgraphs by Airline** | View a filtered subgraph showing only a specific airline's routes |

All features (except booking) support both **terminal-based** and **graphical (SFML)** output modes.

---

## 🏗️ Project Structure

```
DSA/
├── main.cpp              # Entry point — menu loop and user interaction
├── graph.h / graph.cpp   # Core graph class (adjacency list, all search algorithms)
├── flight.h              # Flight entity header
├── layoverqueue.h        # Custom queue for managing layover segments
├── layoverqueue.cpp      # Queue implementation
├── Flights.txt           # Dataset of international flight routes
├── HotelCharges_perday.txt # Hotel cost data (for layover cost calculations)
├── bookings.txt          # Persistent storage for booked flights
├── output.ogg            # Startup audio clip
└── arial.ttf             # Font used by SFML GUI rendering
```

---

## 🧠 Data Structures Used

- **Graph** — Directed weighted graph modelling cities as vertices and flights as edges
- **Adjacency List** — Custom linked-list-based adjacency representation (`node` → `adjlist` → `graph`)
- **Queue** — Custom `LayoverQueue` using linked nodes for managing layover segments during multi-hop route search
- **Arrays** — Fixed-size city name index (`citynames[12]`) mapping city strings to graph indices

---

## ⚙️ Algorithms

- **Graph Traversal** — DFS/BFS-style traversal for route finding and layover discovery
- **Shortest Route** — Greedy/exhaustive search for minimum-cost paths between cities
- **Subgraph Extraction** — Filters the full graph to edges belonging to a single airline
- **Preference Filtering** — Searches routes satisfying both airline and transit city constraints

---

## 🛫 Flight Dataset

Flights are loaded from `Flights.txt` at startup. Each line represents a direct flight in the format:

```
<Source> <Destination> <Date> <DepartureTime> <ArrivalTime> <Cost> <Airline>
```

**Example:**
```
Islamabad NewYork 1/12/2019 11:00 18:00 150000 Emirates
Paris Berlin 1/12/2019 0:30 4:00 25000 Qatar
```

### Cities in the Dataset
`Islamabad` · `NewYork` · `Paris` · `Tokyo` · `London` · `Berlin` · `Amsterdam` · `Singapore` · `HongKong` · `Seoul` · `Sydney`

### Airlines in the Dataset
`Emirates` · `Qatar` · `ANA`

---

## 🖥️ Dependencies

| Dependency | Purpose |
|-----------|---------|
| [SFML](https://www.sfml-dev.org/) ≥ 2.5 | 2D graphics, window management, audio playback |
| C++17 or later | `<thread>`, `<chrono>`, filesystem features |
| Standard Library | `<iostream>`, `<fstream>`, `<iomanip>`, `<string>` |

---

## 🔧 Building & Running

### Prerequisites

1. Install **SFML** and make sure its headers and libraries are on your compiler path.
2. Ensure `arial.ttf`, `output.ogg`, and `Flights.txt` are in the **same directory** as the executable.

### Compile (g++)

```bash
g++ main.cpp graph.cpp layoverqueue.cpp -o FlightSystem -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system -std=c++17
```

### Run

```bash
./FlightSystem
```

On Windows:

```powershell
.\FlightSystem.exe
```

> **Note:** The program plays a startup sound (`output.ogg`) using SFML Audio on launch.

---

## 🗂️ Data Files

| File | Description |
|------|-------------|
| `Flights.txt` | Source flight data loaded into the graph at startup |
| `bookings.txt` | Stores booked flights (append-only, auto-created if missing) |
| `HotelCharges_perday.txt` | Daily hotel costs at layover cities |

---

## 📌 Notes

- The graph supports up to **12 cities** (fixed array size; extend `citynames[12]` and `adjlist a[12]` in `graph.h` to add more).
- City names are **case-sensitive** — use exact names as they appear in `Flights.txt` (e.g., `NewYork`, not `new york`).
- Graphical windows are created per-feature and closed individually after use.
