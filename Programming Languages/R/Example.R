# Load the package required to read/stream in JSON files.
library("jsonlite")

# Opens the file and streams in the filtered data.
result <- subset(stream_in(file("review.data", open = "r")))

result$numOfWords <- sapply(result[3]$reviewText, function(x) length(unlist(strsplit(x, "\\W+"))))

overall1 <- subset(result, overall == 1)
overall2 <- subset(result, overall == 2)
overall3 <- subset(result, overall == 3)
overall4 <- subset(result, overall == 4)
overall5 <- subset(result, overall == 5)

# Counts the number of words in the reviewText column and stores it in a new column
result$numOfWords <- lengths(strsplit(result[3]$reviewText, '\\S+'))
