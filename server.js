const express = require("express");
const app = express();
const path = require("path");
const port = 3000;

// Replace these with your students' MAC addresses
const validMacAddresses = {
  "A2:DE:FD:99:84:82": "Nahid",
  "66:77:88:99:AA:BB": "Student 2",
  "74:FE:CE:F7:3D:85": "unknown",
};

let attendance = {};

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.post("/scan", (req, res) => {
  const mac = req.body.mac;
  console.log(`Received MAC address: ${mac}`); // Log received MAC addresses
  if (validMacAddresses[mac]) {
    attendance[mac] = validMacAddresses[mac];
    console.log(`Marked present: ${validMacAddresses[mac]}`);
  } else {
    console.log(`MAC address ${mac} not recognized`);
  }
  res.send("MAC Address Received");
});

app.get("/attendance", (req, res) => {
  const attendanceArray = Object.keys(attendance).map((mac) => ({
    mac: mac,
    name: attendance[mac],
  }));
  res.json(attendanceArray);
});

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "index.html"));
});

app.listen(port, () => {
  console.log(`Server running at http://192.168.0.109:${port}`);
});
