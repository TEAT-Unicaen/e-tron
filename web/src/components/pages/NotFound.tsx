import { Link } from "react-router-dom";
import BackgroundLayout from "../layout/BackgroundLayout"
import "./NotFound.css";

const NotFound = () => {
    return (
        <div>
            <BackgroundLayout/>
            <div className="loader">
                <div className="box1"></div>
                <div className="box2"></div>
                <div className="box3"></div>
            </div>

            <h1>404 - Page Not Found!</h1>
            <Link to="/">Go Home</Link>

        </div>
    );
};

export default NotFound;
