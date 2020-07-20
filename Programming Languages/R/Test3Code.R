# Loads the library
library("purrr")

# Reads in the csv file
test3data <- read.csv("test3data.csv", header = TRUE, na.strings = c(""))
cherry <- read.csv("cherry.csv", header = TRUE)

# Gets the profit median for month = 6
median(test3data$Profit, na.rm = TRUE, Month = 6)

# Removes all rows with missing industries
test3data <- test3data[!is.na(test3data$Industry),]

# Changes type to char
test3data$State <- as.character(test3data$State)
test3data$City <- as.character(test3data$City)
test3data$Expenses <- as.character(test3data$Expenses)
test3data$Revenue <- as.character(test3data$Revenue)

# Fill in missing data
rownames(test3data) <- NULL
test3data[is.na(test3data$State) & test3data$City=="Jackson", "State"] <- "Mississippi"
test3data[is.na(test3data$State) & test3data$City=="Cheyenne", "State"] <- "Wyoming"
test3data[is.na(test3data$State) & test3data$City=="Sacremento", "State"] <- "California"
test3data[is.na(test3data$Profit), "Profit"] <- mean(test3data$Profit, na.rm = TRUE)

test3data$Expenses <- gsub('[$,]','',test3data$Expenses)
test3data$Expenses <- as.numeric(test3data$Expenses)
test3data[is.na(test3data$Expenses), "Expenses"] <- mean(test3data$Expenses, na.rm = TRUE)
test3data$Expenses <- as.character(test3data$Expenses)
test3data$Expenses <- gsub('^','$',test3data$Expenses)

test3data$Revenue <- gsub('[$,]','',test3data$Revenue)
test3data$Revenue <- gsub(" Dollars","",test3data$Revenue)
test3data$Revenue <- as.numeric(test3data$Revenue)
test3data[is.na(test3data$Revenue), "Revenue"] <- mean(test3data$Revenue, na.rm = TRUE)
test3data$Revenue <- as.character(test3data$Revenue)
test3data$Revenue <- gsub('^','$',test3data$Revenue)
test3data$Revenue <- gsub('$',' Dollars',test3data$Revenue)

# Create a color palette change 2 to any number to increase/decrease color ramping
palette <- colorRampPalette(colors = c("orange", "blue"))(2)

# Make a bar plot with height and volume side by side
barplot(t(as.matrix(cherry[, 2:3])), beside = TRUE, main = "Height vs Volume", xlab = "Diameter", ylab = "Height vs Volume", col = palette, names.arg = cherry$Diam, legend = c("Height", "Volume"))

# Makes a linear regression of height and volume
cherry.lm <- lm(Volume ~ Height, data = cherry)

# Plots Height vs Volume
plot(cherry$Height, cherry$Volume, main = "Height vs Volume", xlab = "Height", ylab = "Volume")

# Plots the linear regression line
abline(cherry.lm)
