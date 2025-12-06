import os
from roboflow import Roboflow
from dotenv import load_dotenv

load_dotenv()

rf = Roboflow(api_key=os.getenv("ROBOFLOW_API_KEY"))
project = rf.workspace("roboflow-58fyf").project("rock-paper-scissors-sxsw")  # cambia si usas otro dataset
dataset = project.version(1).download("yolov8")  # revisa la versión disponible