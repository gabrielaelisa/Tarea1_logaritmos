library(readr)
library(scales)
library(ggplot2)

## funcion para sacar el valor p de una regresion
lmp <- function (modelobject) {
  if (class(modelobject) != "lm") stop("Not an object of class 'lm' ")
  f <- summary(modelobject)$fstatistic
  p <- pf(f[1],f[2],f[3],lower.tail=F)
  attributes(p) <- NULL
  return(p)
}

# leer datos
datos_ord <- read_csv("datosp1cordenamiento.csv")

## regresion lineal
fit = lm(log(y)~log(x), data=datos_ord)
slope <- round(fit$coefficients["log(x)"],3)
error <- round(summary(fit)$coef[2,2],4)
r_squared = summary(fit)$r.squared
p_value = lmp(fit)

## graficar
p <-ggplot(datos_ord,aes(x, y)) 
p + geom_point(size=2) + 
  ggtitle("Gráfico Log Log de Número de Elementos v/s Tiempo de Ordenación") +
  scale_x_continuous(trans='log10', name="Número de Elementos",labels = comma,breaks = c(0,10,100,1000,10000,100000,1000000,10000000)) + 
  scale_y_continuous(trans='log10',name = "Tiempo de Ejecución (nanosegundos)",labels = comma) + 
  annotation_logticks() +
  theme_bw() +
  geom_boxplot(aes(group = x)) + 
  geom_smooth(method="lm") + 
  annotate("text",x=10000/2,y = 10000000*3, hjust=0,label = paste('R² = ', round(r_squared,4))) +
  annotate("text",x=10000/2,y = 1000000*5*3, hjust=0,label = paste('Valor p = ',formatC(p_value, format = "e", digits = 2))) +
  annotate("text",x=10000/2,y = 1000000*2.5*3, hjust=0,label = paste('Pendiente = ',slope, " ± ",error))

