# Load the package required to read/stream in JSON files.
library("jsonlite")

# Opens the file and streams in the filtered data.
result <- subset(stream_in(file("review.data", open = "r")), overall >= 4)
