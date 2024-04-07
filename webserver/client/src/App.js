import logo from './pistashio.png';
import { useState } from 'react';
var sha256 = require('js-sha256').sha256;

function App() {
  const [password, setPassword] = useState("");
  const [hash, setHash] = useState("");
  const [warning, setWarning] = useState("");
  const [status, setStatus] = useState("");
  let hashPassword = (e) => {
    e.preventDefault();

    setHash(sha256(password)); // Using SHA-256 hashing
    console.log(hash)
  }

  let submitHash = (e) => {
    e.preventDefault()
    let hexReg = /[0-9A-Fa-f]{6}/g;
    if (hexReg.test(hash) && hash.length == 64) {
      console.log('valid hash')
      setWarning('')
      setStatus('Calculating ... \n\n\n')
    } else {
      setWarning('invalid hash')
    }
  }

  return (
    <>
      <div className="wrapper">
        <div className="container">
          <div className="center">
            <img src={logo} alt="Pistashio Logo" className="logo-img" />
          </div>


          <div className="spacer"></div>
          <h1>PitSHAchio</h1>

          <h2 style={{ fontSize:"25px"}}>Please enter a hash to crack, or convert a password to one first</h2>
          <form
            id="password"
            action=""
            onSubmit={hashPassword}
          >
            <label htmlFor="passwordInput">Enter Password (letters & numbers only):
            </label>
            <input
              type="text"
              id="passwordInput"
              pattern="[A-Za-z0-9]*"
              title="Only letters and numbers allowed"
              onChange={(e) => { setPassword(e.target.value) }}
              required
            />
            <input type="submit" value="calculate hash" />
          </form>

          <form
            id="hash"
            action=""
            onSubmit={submitHash}
          >
            <input
              id="hashResult"
              type="text"
              value={hash}
              onChange={(e) => { setHash(e.target.value) }}
              pattern="[a-f0-9]{64}"
              title="Please input a 64 digit hexadecimal"
              required
            ></input>

            <input type="submit" value="submit hash" ></input>
          </form>
          <div style={{ color: 'red', fontSize:"25px"}}>{warning}</div>
          <div style={{ fontSize:"25px"}}>{status}</div>
          <br/>
        </div>
      </div>

      <div className="container about-section">
        <h2>About PitSHAchio</h2>
        <p>
          PitSHAchio is a distributed password cracking program designed to crack
          password hashes efficiently using a distributed computing approach. The
          program utilizes SHA-256 hashing  secure password hashing and
          implements distributed computing techniques  efficient password
          cracking. By distributing tasks among compute clients, PitSHAchio can
          handle large password spaces and compute potential passwords in
          parallel, significantly speeding up the cracking process.
        </p>
        <p>
          The project's primary goal is to provide a
          <strong>powerful yet accessible</strong> tool  security professionals
          and enthusiasts to test and evaluate the strength of password hashes.
          PitSHAchio also aims to encourage collaboration and contributions from
          the community to enhance its capabilities and permance.
        </p>
        <p>
          PitSHAchio uses
          distributed computing to brute ce SHA-256 hashes. It also
          provides a user-friendly interface  ease of use and
          integration into existing security workflows. With PitSHAchio, users can
          test and analyze password hashes to identify
          vulnerabilities and improve overall security measures.
        </p>
      </div>

    </>
  );
}

export default App;
