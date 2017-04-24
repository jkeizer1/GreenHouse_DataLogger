var xhttp = new XMLHttpRequest();
var xmlText;

function graphfunction () {

  var chart = nv.models.lineChart()
                .margin({left: 100})  //Adjust chart margins to give the x-axis some breathing room.
                .showLegend(true)       //Show the legend, allowing users to turn on/off line series.
                .showYAxis(true)        //Show the y-axis
                .yDomain([-10, 40])
                .showXAxis(true)        //Show the x-axis
  ;

  chart.xAxis     //Chart x-axis settings
      .axisLabel('Date Time')
      .tickFormat (function(d) {
          return d3.time.format.utc('%m-%d %H:%M')(new Date(d))
      } );
      
  chart.xScale(d3.time.scale()); 
  
  chart.yAxis     //Chart y-axis settings
      .axisLabel('Temperature (C)')
      .tickFormat(d3.format('.02f'));

  var myData;

  myData = getlogdata();   //You need data...

  d3.select('#chart svg')    //Select the <svg> element you want to render the chart in.   
      .datum(myData)         //Populate the <svg> element with chart data...
      .call(chart);          //Finally, render the chart!

  //Update the chart when window resizes.
  nv.utils.windowResize(function() { chart.update() });
  return chart;
};


function getlogdata() {
  var dataread = [];
  var z, i, d, t, t;
  
  var datestring, timestring, timestring2, datetimestring;

  var parser, xmlDoc;

//  alert ("happy 18");
//  alert (xmlText);

  parser = new DOMParser();
  xmlDoc = parser.parseFromString(xmlText, "text/html");

  z = xmlDoc.getElementsByTagName("TEMPC");
//  alert (z.length);
  
  d = xmlDoc.getElementsByTagName("DATE");
  t = xmlDoc.getElementsByTagName("TIME");
  
  for (i = 0; i < z.length; i++) {
     datestring = d[i].childNodes[0].nodeValue;
     timestring = t[i].childNodes[0].nodeValue;
     timestring2 = timestring.replace(".", ":");
     datetimestring = datestring + "T" + timestring + ":00Z";

     dataread.push ( {x: new Date(datetimestring),  y:z[i].childNodes[0].nodeValue} );
  }
  
//  dataread.push ( {x:0, y:2} );
//  dataread.push ( {x:1, y:4} );

  return [
    {
      values: dataread,         //values - represents the array of {x,y} data points
      key: 'Temperature Graph', //key  - the name of the series.
      color: '#ff7f0e'  //color - optional: choose your own line color.
    }
  ];
}


xhttp.onreadystatechange = function () {

    if (this.readyState == 4 && this.status == 200) {
       // Typical action to be performed when the document is ready:
       //     document.getElementById("dataout").innerHTML = xhttp.responseText;
       xmlText = xhttp.responseText;
       nv.addGraph (graphfunction);
    } else if (this.readyState == 0)
    {
        alert ("request not initialized");
    }
};

function error_function (evt) {
    alert ("xhttp XMLTttpRequest Error Alert fired");
}

function abort_function (evt) {
    alert ("xhttp XMLTttpRequest abort Alert fired");
}

xhttp.addEventListener("error", error_function);
xhttp.addEventListener("abort", abort_function);
xhttp.open("GET", '/data/datalog.txt', true);
xhttp.send();