# Load the package required to read/stream in JSON files.
library("jsonlite")

# Opens the file and streams in the data.
result <- subset(stream_in(file("review.data", open = "r")))

# Counts the number of words in the reviewText column and stores it in a new column
result$numOfWords <- lengths(strsplit(result$reviewText, '\\S+'))

overall1 <- subset(result, overall == 1)
overall2 <- subset(result, overall == 2)
overall3 <- subset(result, overall == 3)
overall4 <- subset(result, overall == 4)
overall5 <- subset(result, overall == 5)

# Sums up the number of words and divides them by the number of rows
wps1 <- sum(overall1$numOfWords)/nrow(overall1)
wps2 <- sum(overall2$numOfWords)/nrow(overall2)
wps3 <- sum(overall3$numOfWords)/nrow(overall3)
wps4 <- sum(overall4$numOfWords)/nrow(overall4)
wps5 <- sum(overall5$numOfWords)/nrow(overall5)

df <- data.frame("1", wps1)
names(df) <- c("Overall", "WPS")

de <- data.frame("2", wps2)
names(de) <- c("Overall", "WPS")
df <- rbind(df, de)

de <- data.frame("3", wps3)
names(de) <- c("Overall", "WPS")
df <- rbind(df, de)

de <- data.frame("4", wps4)
names(de) <- c("Overall", "WPS")
df <- rbind(df, de)

de <- data.frame("5", wps5)
names(de) <- c("Overall", "WPS")
df <- rbind(df, de)

# Plots Overall levels vs Words per Sentences
df$Overall <- as.numeric(as.character(df$Overall))
plot(df$Overall, df$WPS, main = "Overall vs WPS", xlab = "Overall", ylab = "WPS", type = "b")
print(df)
