*This project has been created as part of the 42 curriculum by jtardieu*

# 🏃‍♂️ Codexion

<table>
  <tr>
    <td>
      <img src="https://media1.tenor.com/m/tg4TVGJwlSgAAAAC/math-wtf.gif"width="200">
    </td>
    <td align="center">
      <h2>Master the race before the deadline masters yee</h2>
    </td>
	<td>
      <img src="https://media1.tenor.com/m/1DwPMqeXJ-MAAAAC/okay-okay-gif.gif" width="200">
    </td>
  </tr>
</table>

# Description

**Codexion** is a thrilling concurrency challenge where multiple coders compete for limited USB dongles in a shared quantum coding hub.

Think of it like this: 🎯
- 4️⃣ coders, all desperately wanting to compile
- 4️⃣ USB dongles
- ⏰ A race against time before BURNOUT 🔥

Master **thread synchronization**, avoid **deadlocks**, and keep everyone from going insane!

## 🚀 Quick Start

```bash
make
./codexion 4 800 200 200 100 5 50 edf
```

## ⚙️ How to Run

| Command | What it does |
|---------|-------------|
| `make` | 🏗️ Compile the project |
| `make clean` | 🧹 Remove object files |
| `make fclean` | 🗑️ Remove everything (including binary) |
| `make re` | 🔄 Rebuild from scratch |

## 📋 Parameters Explained

```bash
./codexion <coders> <burnout> <compile> <debug> <refactor> <required> <cooldown> <scheduler>
```

| Parameter | Example | What it means |
|-----------|---------|---------------|
| `coders` | 4 | Number of coders competing |
| `burnout` | 800 | Milliseconds before a coder melts down 🔥 |
| `compile` | 200 | Time to compile (ms) |
| `debug` | 200 | Time to debug (ms) |
| `refactor` | 100 | Time to refactor (ms) |
| `required` | 5 | Compiles each coder needs to do |
| `cooldown` | 50 | Dongle recovery time (ms) |
| `scheduler` | `fifo` or `edf` | Who gets the dongle first? |

## 🎮 Example Runs

### 🔥 Easy Mode
```bash
./codexion 2 2000 200 100 100 3 50 fifo
```

### 😰 Medium Mode
```bash
./codexion 4 800 200 200 100 5 50 edf
```

### 💀 Hard Mode
```bash
./codexion 8 400 200 200 100 10 100 edf
```

## 🧵 Threading Architecture

| Component | Job |
|-----------|-----|
| 🧑‍💻 **Coder Threads** | Compete for dongles, compile, debug, refactor |
| 🎛️ **Monitor Thread** | Watches for burnouts & completion |
| 🔐 **Mutexes** | Protects shared dongle state |
| 🔔 **Condition Variables** | Efficient thread wake-ups |

## 🎯 Key Concepts Implemented

### ✅ Deadlock Prevention
- **Lock Ordering** 🔑: Always grab dongles in ascending ID order

## 📚 Resources

### Threading & Concurrency
- [POSIX Threads Manual](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [pthread_mutex](https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html)
- [pthread_cond](https://man7.org/linux/man-pages/man3/pthread_cond_wait.3p.html)

### Scheduling
- **Coffman's Conditions** for Deadlock
- **Lock Ordering** Technique
- **Earliest Deadline First (EDF)** Scheduling

### 🙏 Human Help

| Person | Contribution |
|--------|--------------|
| 👤 **aspenle** | Helped me understand mutexes & synchronization concepts |
| 👤 **agilliard** | Debugged race conditions & deadlock issues |

Huge thanks to them! 💪

## 🤖 AI Usage

| What | Tool | How |
|------|------|-----|
| 🐛 Debugging | **Claude** | Race condition & deadlock analysis & fixes |
| 💬 VS Code Copilot | **GitHub Copilot** | Code suggestions & snippets |

**Human stayed in charge of:** Understanding every line, testing, final decisions, and making sure it actually works! 💪

**Claude was the main AI partner** - helpful for understanding some problems, and implementing solutions correctly! 🔥

## 🎓 What I Learn

✅ POSIX thread creation & management  
✅ Mutual exclusion & resource protection  
✅ Condition variables & efficient waiting  
✅ Scheduling policies & fairness  
✅ Deadlock prevention techniques  
✅ Real-time monitoring & synchronization

---