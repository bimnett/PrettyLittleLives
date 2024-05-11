<template>
    <h1>Jobs</h1>
    <div v-for="job in jobs" :key=job.id>
            <h2> {{  job.title }}</h2>
           
    </div>
</template>

<script>

export default {
    data() {
        return{
            jobs: [
                {title: 'Ling', id: 1, details: 'test data and info'},
                {title: 'William', id: 2, details: '2 test data and info 2'},
                {title: 'Semlan', id: 3, details: '3 test data and info 3'}
            ]

        }
    },
}
</script>

<style>

</style>