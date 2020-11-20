package yoda

import (
	"net/http"
	"sync/atomic"

	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promhttp"
)

type yodaCollector struct {
	context                   *Context
	reportsHandlingGaugeDesc  *prometheus.Desc
	reportsPendingGaugeDesc   *prometheus.Desc
	reportsSubmittedCountDesc *prometheus.Desc
}

func NewYodaCollector(c *Context) prometheus.Collector {
	return &yodaCollector{
		context: c,
		reportsHandlingGaugeDesc: prometheus.NewDesc(
			"yoda_reports_handling",
			"Number of reports currently being handled",
			[]string{"state"}, nil),
		reportsPendingGaugeDesc: prometheus.NewDesc(
			"yoda_reports_pending",
			"Number of reports currently pending for submission",
			[]string{"state"}, nil),
		reportsSubmittedCountDesc: prometheus.NewDesc(
			"yoda_reports_submitted_count",
			"Number of reports submitted since last yoda restart",
			[]string{"state"}, nil),
	}
}

func (collector yodaCollector) Describe(ch chan<- *prometheus.Desc) {
	ch <- collector.reportsHandlingGaugeDesc
	ch <- collector.reportsPendingGaugeDesc
	ch <- collector.reportsSubmittedCountDesc
}

func (collector yodaCollector) Collect(ch chan<- prometheus.Metric) {
	ch <- prometheus.MustNewConstMetric(collector.reportsHandlingGaugeDesc, prometheus.GaugeValue,
		float64(atomic.LoadInt64(&collector.context.handlingGauge)), "handling")
	ch <- prometheus.MustNewConstMetric(collector.reportsPendingGaugeDesc, prometheus.GaugeValue,
		float64(atomic.LoadInt64(&collector.context.pendingGauge)), "pending")
	ch <- prometheus.MustNewConstMetric(collector.reportsSubmittedCountDesc, prometheus.CounterValue,
		float64(atomic.LoadInt64(&collector.context.submittedCount)), "submitted")
}

func metricsListen(listenAddr string, c *Context) {
	collector := NewYodaCollector(c)
	prometheus.MustRegister(collector)
	http.Handle("/metrics", promhttp.Handler())
	panic(http.ListenAndServe(listenAddr, nil))
}
