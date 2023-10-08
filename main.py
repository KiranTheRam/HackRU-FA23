from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import optimized_version as sp
app = FastAPI()

class SongRequest(BaseModel):
    title: str


@app.post("/song/")
async def create_song(song: SongRequest):
    saved_list = sp.search_and_play_song(song.title)
    print(saved_list)
    return saved_list
