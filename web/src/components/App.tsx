import { BrowserRouter as Router, Routes, Route } from "react-router-dom";
import { FileDataProvider } from '../store/json'
import './App.css'

import Home from '../components/pages/Home'
import Viewer from '../components/pages/Viewer'
import NotFound from "./pages/NotFound";
import TimeLine from "./pages/Timeline";
import Compare from "./pages/Compare";

function App() {
  return (
    <FileDataProvider>
      <Router>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/viewer" element={<Viewer />} />
          <Route path="timeline" element={<TimeLine />} />
          <Route path="/compare" element={<Compare />} />
          <Route path="*" element={<NotFound />} />
        </Routes>
      </Router>
    </FileDataProvider>
  )
}

export default App
